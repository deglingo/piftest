/* piftest.c -
 */

#include "piftest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* [REMOVEME] */
#define MAX_TESTS 1024

typedef struct _PifTest PifTest;



/* PifTest:
 */
struct _PifTest
{
  char *path;
  PifTestFunc func;
};



/* PifSuite:
 */
struct _PifSuite
{
  char *name;
  PifTest tests[MAX_TESTS];
  int n_tests;
};



/* pif_suite_new:
 */
PifSuite *pif_suite_new ( const char *name )
{
  PifSuite *suite;
  suite = malloc(sizeof(PifSuite));
  suite->name = strdup(name);
  suite->n_tests = 0;
  return suite;
}



/* pif_suite_register_unit:
 */
void pif_suite_register_unit ( PifSuite *suite,
                               const char *path )
{
}



/* pif_suite_register_test:
 */
void pif_suite_register_test ( PifSuite *suite,
                               const char *path,
                               PifTestFunc func )
{
  PifTest *test;
  if (suite->n_tests == MAX_TESTS) {
    fprintf(stderr, "[TODO] MAX_TESTS reached (%d)\n", MAX_TESTS);
    abort();
  }
  test = &suite->tests[suite->n_tests++];
  test->path = strdup(path);
  test->func = func;
}



/* pif_suite_run:
 */
void pif_suite_run ( PifSuite *suite,
                     const char *path )
{
}
