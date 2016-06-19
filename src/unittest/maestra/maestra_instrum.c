/**
    \brief maestra implementation of functions used in
        maestra instrumentation of C keywords

   Version control:
    $Date: 2008/10/29 $
	$Change: 240 $
	$Id: //depot/maestra/maestra_instrum.c#5 $
*/
/* Copyright (C) 2007 MacroExpressions.
   Permission is granted to freely use and modify this file provided this
   comment block is retained verbatim.
*/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "maestra_implem.h"
#include "maestra_api.h"



/** Not widely publicized but a way for harness to disable/reenable
the instrumentation output
*/
int maestra_suppress = 0;

/* Definitions of signatures the `if' instrumentation must watch for before
producing any output - or doing any other instrumentation-related activities.
The definition CALLER_XYZ absolutely MUST be kept in sync with the corresponding
MAESTRA_XYZ, or the output will become somewhat funny.
*/
#define CALLER_FOR "maestra_announce(\"FOR\"" /*`for' instrum signature*/
#define CALLER_FOR1 "maestra_announce(\"LOOP_BODY\"" /*`for' instrum signature*/
#define CALLER_DEFAULT "maestra_announce(\"DEFAULT\"" /*`default' instrum signature*/
#define CALLER_CASE "(maestra_announce_ll(\"CASE\"" /*`case' instrum signature*/
#define CALLER_RETURN "maestra_announce(\"RETURN\"" /*`return' instrum signature*/
#define CALLER_BREAK "maestra_announce(\"BREAK\"" /*`break' instrum signature*/
#define CALLER_CONTINUE "maestra_announce(\"CONTINUE\"" /*`continue' instrum signature*/
#define CALLER_GOTO "maestra_fail(\"GOTO\"" /*`goto' instrum signature*/
typedef struct callerid_t {
    const char *signature;
    size_t length; /*without terminating '\0'*/
} callerid_t;

/*A table of signatures suppressing the instrumentation*/
#define CALLERID(literal) {literal, sizeof(literal)-1}
static const callerid_t callerid[] = {
    CALLERID(CALLER_FOR),
    CALLERID(CALLER_FOR1),
    CALLERID(CALLER_DEFAULT),
    CALLERID(CALLER_CASE),
    CALLERID(CALLER_RETURN),
    CALLERID(CALLER_BREAK),
    CALLERID(CALLER_CONTINUE),
    CALLERID(CALLER_GOTO),
};

/*  If an `if' statement happens to result from instrumentation of another
    keyword, we don't want any instrumentation output from it.
    issilent returns a zero iff we want to suppress the output.
*/
static int issilent(const char *call, const callerid_t *id, size_t len)
{
    size_t i;
    for(i=0; i<len; i++) {
        if(memcmp(call, id[i].signature, id[i].length) == 0) {
            return 0; /*matched*/
        }
    }
    return 1;
}

/*Instrumentation of if and ISTRUE*/
int maestra_condition(const char *opname,
                     const char *condition_name,
                     int condition,
                     const char *filename,
                     int line,
                     const char *function_name)
{
    /* Suppress output if it is asked to be suppressed or
        if the caller is a `for' instrumentation
    */
    if(!maestra_suppress && issilent(condition_name, callerid, NELEM(callerid)) != 0) {
        printf("%s\"%s\" %d %s %s %s%s\n",
            MAESTRA_INSTRUM_PREFIX,
            filename,
            line,
            function_name,
            opname,
            /* condition_name, */
            (condition)?"1":"0",
            MAESTRA_INSTRUM_SUFFIX
                );
    }
    return condition;
}



/*Instrumentation of `while'*/
static const callerid_t while_idioms[] = {
    CALLERID("0"),
    CALLERID("1"),
};
int maestra_while(const char *condition_name,
                 int condition,
                 const char *filename,
                 int line,
                 const char *function_name)
{
    int s = maestra_suppress;
    if(!s && issilent(condition_name, while_idioms, NELEM(while_idioms))!=0) {
        printf("%s\"%s\" %d %s WHILE %s %s\n",
            MAESTRA_INSTRUM_PREFIX,
            filename,
            line,
            function_name,
            /* condition_name, */
            (condition)?"1":"0",
            MAESTRA_INSTRUM_SUFFIX
                );
    }
    return condition;
}

/*Instrumentation of for, break, continue, default*/
int maestra_false = 0; /*needed to fool the compiler*/
static unsigned char maestra_suppress_goto = 0; /*needed for default and case instrum*/

int maestra_announce(const char *opname,
                     int retval,
                     const char *filename,
                     int line,
                     const char *function_name)
{
    if(strcmp(opname, "DEFAULT") == 0) {
        maestra_suppress_goto = 1;
    }
    if(!maestra_suppress) {
        printf("%s\"%s\" %d %s %s %s\n",
            MAESTRA_INSTRUM_PREFIX,
            filename,
            line,
            function_name,
            opname,
            MAESTRA_INSTRUM_SUFFIX
                );
    }
    return retval;
}

/*Instrumentation of `switch' and `case'*/
int maestra_announce_ll(const char *opname,
                             const char *condition_name,
                             int condition,
                             const char *filename,
                             int line,
                             const char *function_name)
{
    if(strcmp(opname, "CASE") == 0) {
        maestra_suppress_goto = 1;
    }
    if(!maestra_suppress) {
        printf("%s[%s:%d] %s: Hit `%s\'(%s value %d)%s\n",
            MAESTRA_INSTRUM_PREFIX,
            filename,
            line,
            function_name,
            opname,
            condition_name,
            condition,
            MAESTRA_INSTRUM_SUFFIX
                );
    }
    return condition;
}

maestra_result_t maestra_result;

/*Instrumentation of `goto' and, for some policies, `continue'*/
int maestra_fail(const char *opname,
                 int retval,
                 const char *filename,
                 int line,
                 const char *function_name)
{
    if(strcmp(opname, "GOTO") == 0 && maestra_suppress_goto != 0) {
        /*allow as part of instrumentation*/
    }
    else {
        /*We never suppress the message*/
        printf("%s[%s:%d] %s: Hit disallowed `%s\' %s %s\n",
            MAESTRA_INSTRUM_PREFIX,
            filename,
            line,
            function_name,
            opname,
            MAESTRA_INSTRUM_SUFFIX,
            MAESTRA_RESULT_FAILED
                );
        maestra_result = fail;
    }
    maestra_suppress_goto = 0;
    return retval;
}

/*instrumentation for || and &&*/
int maestra_logical_orand(const char *opname,
                             const char *exp_name,
                             int retval,
                             const char *filename,
                             int line,
                             const char *function_name)
{
    if(!maestra_suppress) {
        printf("%s[%s:%d] %s: %s %s is %s%s\n",
            MAESTRA_INSTRUM_PREFIX,
            filename,
            line,
            function_name,
            opname,
            exp_name,
            (retval)?"true":"false",
            MAESTRA_INSTRUM_SUFFIX
                );
    }
    return retval;
}

