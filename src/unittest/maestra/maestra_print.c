/**
    \brief A set of maestra routines for harness output

Harness output includes output of comparisons of expected vs. actually
computed values.
In that area,
 - a simplest implementation of integer and floating point comparisons is
   provided
 - conspicously absent are implementations of string and raw memory buffers
   comparisons. They are equally straightforward to implement and may be added
   in the near future.

   Version control:
    $Date: 2007/08/26 $
	$Change: 203 $
	$Id: //depot/maestra/maestra_print.c#2 $
*/
/* Copyright (C) 2007 MacroExpressions.
   Permission is granted to freely use and modify this file provided this
   comment block is retained verbatim.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "maestra_api.h"

/** \brief A routine to print a test set header, with completeness checks
\param testnum - the test's consecutive number
\param description - a pointer to the test set description
*/
void maestra_print_description(const char *description)
{
    if(description == NULL) {
        printf("Missing test set description %s\n", MAESTRA_RESULT_FAILED);
        maestra_result_set = fail;
    }
    else {
        printf("%s\n", description);
    }
}

/** Test result conversion-to-string table */
static const char * const tresult[] = {
    MAESTRA_RESULT_PASSED,
    MAESTRA_RESULT_ACCEPTED,
    MAESTRA_RESULT_FAILED,
};

/** \brief A routine to print a test header, with completeness checks
\param testnum - the test's consecutive number
\param test - a pointer to the test definition
*/
void maestra_print_testhead(int testnum, const maestra_test_t *test)
{
    if(test == NULL) {
        /*No more tests; wrap up instead*/
        printf("%d tests executed. Overall test set result: %s\n",
               testnum, tresult[maestra_result_set]);
        return;
    }

    if(test->description == NULL) {
        printf("Test %d: Missing test description %s\n", testnum, MAESTRA_RESULT_FAILED);
        maestra_result_test = fail;  /*force 'em to have a test description*/
    }
    else {
        printf("Test %d: %s\n", testnum, test->description);
    }

    if(test->accept_a == NULL && test->accept_m == NULL) {
        /*no acceptance criteria*/
        printf("! Missing accptance criteria %s\n", MAESTRA_RESULT_FAILED);
        maestra_result_test = fail;  /*force 'em to have it*/
    }
    else {
        printf("Test acceptance criteria:\n");
        if(test->accept_a != NULL) {
            printf("Automatic: %s\n", test->accept_a);
        }
        if(test->accept_m != NULL) {
            printf("Manual: %s\n", test->accept_m);
        }
    }
}

/** \brief A simple wrapper to print the test result
\param result - a result to print in text form
\param scope - the scope's name - test case, test or test set
*/
void maestra_print_result(maestra_result_t result, const char *scope)
{
    printf("Overall %s result: %s\n", scope, tresult[result]);
}

/* ******************************************************************/
/* Simple reference implementations of comparisons within test cases
long long and long double types seem mighty enough to hold smaller
promoted values.
If efficiency becomes an issue or there are types like unsigned long
long in the code, more specialized comparison functions should be
written.
*/

/** \brief An integer-types test for use in specific harness.

The function prints the result of comparison and whether it is considered
passed, accepted, or failed. It also propagates the error to the test case
level.
It is a lazy implementation with no care for efficiency: All integral-type
numbers will be promoted to long long.
\param a - value expected by the harness
\param b - value actually computed by the UUT
\param tolerance - a max error for the acceptance.
*/
void maestra_intcmp(long long a, long long b, int tolerance)
{
    maestra_result_t r;
    long long diff = llabs(a-b);
    if(diff == 0) {
        r = pass;
    }
    else if(diff < tolerance) {
        r = accept;
    }
    else {
        r = fail;
    }
    printf("Expected %lld vs. Actual %lld: %s\n", a, b, tresult[r]);

    /*Propagate the worst result*/
    if(maestra_result_case < r) {
        maestra_result_case = r;
    }
}

/** \brief A floting-point test for use in specific harness.

The function prints the result of comparison and whether it is considered
passed, accepted, or failed. It also propagates the error to the test case
level.
The implementation is relative to the magnitude of the
things we are comparing. A tolerance = 0.5 is reasonably generous.
It is also a lazy implementation with no care for efficiency: All floating
point numbers will be promoted to long double.
\param a - value expected by the harness
\param b - value actually computed by the UUT
\param tolerance - an error scaler for the acceptance.
*/
void maestra_floatcmp(long double a, long double b, double tolerance)
{
    maestra_result_t r;
    long double diff = fabs(a-b);
    if(diff == 0.) {
        /*Yes, there are cases where the results must be bit-true!*/
        r = pass;
    }
    else if(diff < tolerance * (fabs(a)+fabs(b)) * FLT_EPSILON ) {
        r = accept;
    }
    else {
        r = fail;
    }
    printf("Expected %Lf vs. Actual %Lf: %s\n", a, b, tresult[r]);

    /*Propagate the worst result*/
    if(maestra_result_case < r) {
        maestra_result_case = r;
    }
}


