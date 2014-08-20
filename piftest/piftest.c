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
  int data_size;
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
 *
 * [FIXME] data_size should be registered for unts only
 */
void pif_suite_register_test ( PifSuite *suite,
                               const char *path,
                               PifTestFunc func,
                               int data_size )
{
  PifTest *test;
  if (suite->n_tests == MAX_TESTS) {
    fprintf(stderr, "[TODO] MAX_TESTS reached (%d)\n", MAX_TESTS);
    abort();
  }
  test = &suite->tests[suite->n_tests++];
  test->path = strdup(path);
  test->func = func;
  test->data_size = data_size;
}



/* pif_suite_run:
 */
void pif_suite_run ( PifSuite *suite,
                     const char *path )
{
  int n;
  fprintf(stderr, "%s: running %d test(s)...\n", suite->name, suite->n_tests);
  for (n = 0; n < suite->n_tests; n++)
    {
      void *data;
      if (suite->tests[n].data_size) {
        data = malloc(suite->tests[n].data_size);
        memset(data, 0, suite->tests[n].data_size);
      } else {
        data = NULL;
      }
      suite->tests[n].func(data);
      fprintf(stderr, ".");
      if (data)
        free(data);
    }
  fprintf(stderr, "\n");
}
