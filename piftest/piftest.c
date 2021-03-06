/* piftest.c -
 */

#include "piftest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>



/* [REMOVEME] */
#define MAX_TESTS 1024
#define MAX_GLOBAL_SETUP 16

/* [REMOVEME] */
/* #define VERBOSE */

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

  PifGlobalSetupFunc global_setup[MAX_GLOBAL_SETUP];
  int global_setup_count;
  /* [REMOVEME] */
  PifTest tests[MAX_TESTS];
  int n_tests;
};



/* _valgrind_command:
 */
static char **_valgrind_command ( PifConfig *config )
{
  int cmdsize = 32;
  char **cmd = malloc(sizeof(char *) * cmdsize);
  char **supp;
  int nargs = 0;
  cmd[nargs++] = "valgrind";
  cmd[nargs++] = "--quiet";
  cmd[nargs++] = "--tool=memcheck";
  cmd[nargs++] = "--leak-check=yes";
  cmd[nargs++] = "--show-possibly-lost=yes";
  cmd[nargs++] = "--leak-resolution=high";
  cmd[nargs++] = "--show-reachable=yes";
  cmd[nargs++] = "--undef-value-errors=yes";
  /* cmd[nargs++] = "--track-origins=yes"; */
  cmd[nargs++] = "--fullpath-after=";
  /* [FIXME] this option looks usefull but the produced traceback is
     not clear */
  cmd[nargs++] = "--track-fds=yes";
  cmd[nargs++] = "--num-callers=50";
  cmd[nargs++] = "--show-below-main=yes";
  cmd[nargs++] = "--read-var-info=yes";
  cmd[nargs++] = "--gen-suppressions=all";
  for (supp = config->valgrind_supp_files; *supp; supp++) {
    /* [FIXME] assert nargs < cmdsize */
    char *opt = malloc(strlen("--suppressions=") + strlen(*supp) + 1);
    sprintf(opt, "--suppressions=%s", *supp);
    cmd[nargs++] = opt;
  }
  cmd[nargs++] = config->argv[0];
  cmd[nargs++] = "-R";
  cmd[nargs++] = NULL;
  return cmd;
}



/* piftest_main:
 */
int piftest_main ( PifConfig *config )
{
  int r;
  if (config->argc > 1 && !strcmp(config->argv[1], "-R"))
    {
      r = config->main_func();
      /* close standard fds so they are not reported by valgrind */
      close(0);
      close(1);
      close(2);
      return r;
    }
  else
    {
      char **cmd = _valgrind_command(config);
      /* { */
      /*   char **a; */
      /*   fprintf(stderr, ">"); */
      /*   for (a = cmd; *a; a++) */
      /*     fprintf(stderr, " %s", *a); */
      /*   fprintf(stderr, "\n"); */
      /* } */
      execvp("valgrind", cmd);
      fprintf(stderr, "exec(valgrind) failed!\n");
      abort();
    }
}



/* pif_suite_new:
 */
PifSuite *pif_suite_new ( const char *name )
{
  PifSuite *suite;
  suite = malloc(sizeof(PifSuite));
  memset(suite, 0, sizeof(PifSuite));
  suite->name = strdup(name);
  suite->n_tests = 0;
  return suite;
}



/* pif_suite_destroy:
 */
void pif_suite_destroy ( PifSuite *suite )
{
  int s;
  for (s = 0; s < suite->n_tests; s++)
    free(suite->tests[s].path);
  free(suite->name);
  free(suite);
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



/* pif_suite_register_global_setup:
 */
void pif_suite_register_global_setup ( PifSuite *suite,
                                       PifGlobalSetupFunc func )
{
  if (suite->global_setup_count >= MAX_GLOBAL_SETUP) {
    fprintf(stderr, "[TODO] MAX_GLOBAL_SETUP reached\n");
    abort();
  } 
  suite->global_setup[suite->global_setup_count++] = func;
}



/* pif_suite_run:
 */
void pif_suite_run ( PifSuite *suite,
                     const char *path )
{
  int n;
  fprintf(stderr, "%s: running %d test(s)...\n", suite->name, suite->n_tests);
  /* global setups */
  for (n = 0; n < suite->global_setup_count; n++)
    suite->global_setup[n]();
  /* tests */
  for (n = 0; n < suite->n_tests; n++)
    {
      void *data;
      if (suite->tests[n].data_size) {
        data = malloc(suite->tests[n].data_size);
        memset(data, 0, suite->tests[n].data_size);
      } else {
        data = NULL;
      }
#ifdef VERBOSE
      fprintf(stderr, "== %s :\n", suite->tests[n].path);
#endif
      suite->tests[n].setup(data);
      suite->tests[n].func(data);
      suite->tests[n].teardown(data);
#ifndef VERBOSE
      fprintf(stderr, ".");
#endif
      if (data)
        free(data);
    }
#ifndef VERBOSE
  fprintf(stderr, "\n");
#endif
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
        case 'i':
          fprintf(stderr, "%d", va_arg(args, int));
          break;
        case 's':
          fprintf(stderr, "%s", va_arg(args, const char *));
          break;
        case 'p':
          fprintf(stderr, "%p", va_arg(args, void *));
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
