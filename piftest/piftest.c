/* piftest.c -
 */

#include "piftest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


/* [REMOVEME] */
#define MAX_TESTS 1024

typedef enum _PifNodeType PifNodeType;
typedef union _PifNode PifNode;
typedef struct _PifNodeAny PifNodeAny;
typedef struct _PifTest PifTest;

#define PIF_NODE_HEADER \
  PifNodeType type; \
  PifNode *parent; \
  char *name; \
  char *path;



/* PifNodeType:
 */
enum _PifNodeType
  {
    PIF_NODE_TEST,
  };



/* PifNodeAny:
 */
struct _PifNodeAny
{
  PIF_NODE_HEADER;
};



/* PifTest:
 */
struct _PifTest
{
  PIF_NODE_HEADER;
  PifTestFunc func;
  /* [REMOVEME] (should go in PifUnit) */
  int data_size;
  PifSetupFunc setup;
  PifTeardownFunc teardown;
};



/* PifNode:
 */
union _PifNode
{
  PifNodeType type;
  PifNodeAny any;
  PifTest test;
};



/* PifSuite:
 */
struct _PifSuite
{
  char *name;

  /* [REMOVEME] */
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
 * [FIXME] data_size, setup and teardown should be registered for unts
 * only
 */
void pif_suite_register_test ( PifSuite *suite,
                               const char *path,
                               PifTestFunc func,
                               int data_size,
                               PifSetupFunc setup,
                               PifTeardownFunc teardown )
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
  test->setup = setup;
  test->teardown = teardown;
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
      suite->tests[n].setup(data);
      suite->tests[n].func(data);
      suite->tests[n].teardown(data);
      fprintf(stderr, ".");
      if (data)
        free(data);
    }
  fprintf(stderr, "\n");
}



/* pif_check:
 */
void pif_check ( const char *fname,
                 int lineno,
                 int expr,
                 const char *sexpr,
                 ... )
{
  va_list args;
  const char *vname;
  if (expr)
    {
      /* success */
      return;
    }
  else
    {
      fprintf(stderr, "\n%s:%d: TEST FAILED:\n -> `%s'\n",
              fname, lineno, sexpr);
    }
  va_start(args, sexpr);
  while ((vname = va_arg(args, const char *)))
    {
      fprintf(stderr, "  - %s = ", vname);
      const char *vtp = va_arg(args, const char *);
      switch(vtp[0])
        {
        case 's':
          fprintf(stderr, "%s", va_arg(args, const char *));
          break;
        default:
          fprintf(stderr, "\n[TODO] vtp '%s'", vtp);
          abort();
        }
      fprintf(stderr, "\n");
    }
  va_end(args);
  abort();
}
