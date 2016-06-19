/**
    \brief maestra API for writing stubs and specific harness

NOTE: This is the first (and rather sloppy) organization: some things
are applicable to internal maestra workings and should not be exposed
to a stub/harness programmer. The problem is, for some items I am not
sure whether they should or should not be exposed, so for now almost
everything is thrown in one bin.

   Version control:
    $Date: 2007/08/26 $
	$Change: 203 $
	$Id: //depot/maestra/maestra_api.h#2 $
*/
/* Copyright (C) 2007 MacroExpressions.
   Permission is granted to freely use and modify this file provided this
   comment block is retained verbatim.
*/

#ifndef MAESTRA_API_H_
#define MAESTRA_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!Just a handy macro for the number of elements in an array*/
#ifndef NELEM
#define NELEM(array) (sizeof(array)/sizeof((array)[0]))
#endif

/*!The type of test execution result */
typedef enum maestra_result_t {
    pass,
    accept,
    fail
} maestra_result_t;

extern maestra_result_t maestra_result;   /*! result of the last evaluation*/
extern maestra_result_t maestra_result_set; /*! (running) result of the whole test*/
extern maestra_result_t maestra_result_test; /*! (running) result of the current test*/
extern maestra_result_t maestra_result_case; /*! result of the last test case*/

extern int maestra_count; /*! number of test case executions so far*/

/** The type of test case definition */
typedef struct maestra_testcase_t {
    void *arg;
    void (*test_func)(void *arg);
    int repeat; /*!< number of reperitions of the case*/
} maestra_testcase_t;

#define MAESTRA_TESTCASE_END {.test_func = NULL,} /*! terminates a test case array*/

/** The type of test as a collection of test cases */
typedef struct maestra_test_t {
    const char *description; /*!< what the test is about*/
    const char *accept_a;    /*!< automatic acceptance criteria stated*/
    const char *accept_m;    /*!< manual acceptance criteria stated*/
    const maestra_testcase_t *maestra_testcase; /*!< an array of test cases*/
    void (*init_func)(void); /*!< Test initialization function (optional)*/
    void (*cleanup_func)(void); /*!< Test cleanup function (optional)*/
} maestra_test_t;
#define MAESTRA_TEST_END {.maestra_testcase = NULL,} /*! terminates a test array*/

/** The type of test set as a collection of tests */
typedef struct maestra_testset_t {
    const char *description;  /*!< Test set description*/
    void (*init_func)(void); /*!< Test set initialization function*/
    const maestra_test_t *maestra_test;  /*!< A pointer to a NULL-terminated array of tests*/
} maestra_testset_t; /*! test set type, with a single instance in the program*/

/*Print stuff*/
extern void maestra_print_description(const char *description);
extern void maestra_print_testhead(int testnum, const maestra_test_t *test);
extern void maestra_print_result(maestra_result_t result, const char *scope);

/*Data checking to use in harness or stubs*/
extern void maestra_intcmp(int a, int b, int tolerance);
extern void maestra_floatcmp(long double a, long double b, double tolerance);

/** Print formatting to ensure the source of output is conspicuous */
/* I am not sure yet whether these should be string literals or constant
   strings somewhere. The implementation and the example may show
   this ambiguity.
*/
#ifdef HTML_OUT
    /*TODO*/
#else
    /*Plain text*/
#define MAESTRA_INSTRUM_PREFIX "<MINST> "
#define MAESTRA_INSTRUM_SUFFIX ""
#define MAESTRA_HARNESS_PREFIX "<MHARN> "
#define MAESTRA_HARNESS_SUFFIX ""
#define MAESTRA_STUB_PREFIX "<MSTUB> "
#define MAESTRA_STUB_SUFFIX ""
#define MAESTRA_INSTRUM_INIT_PREFIX "<MINIT> "
#define MAESTRA_INSTRUM_INIT_SUFFIX ""

#define MAESTRA_FALSE_STRING "0"
#define MAESTRA_TRUE_STRING "1"

#define MAESTRA_RESULT_PASSED "PASSED"
#define MAESTRA_RESULT_ACCEPTED "ACCEPTED"
#define MAESTRA_RESULT_FAILED "FAILED"
#endif /*HTML_OUT*/

/** The instance of the test set, must be provided by specific harness */
extern const maestra_testset_t maestra_testset;

#ifdef __cplusplus
}
#endif

#endif /*MAESTRA_API_H_*/
