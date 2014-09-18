/* piftools.h -
 */

#ifndef _PIFTOOLS_H_
#define _PIFTOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PIF_CHECK(expr) do {                                \
    if (!(expr)) {                                          \
      fprintf(stderr, "%s:%d: test failed: `" #expr "'\n",  \
              __FILE__, __LINE__);                          \
      exit(1);                                              \
    }                                                       \
  } while (0)

#define _PIF_CHECK(expr, sexpr, values...)      \
  pif_check(__FILE__, __LINE__,                 \
            (expr), sexpr, values)

#define PIF_CHECK_EQ_STR(a, b) do {           \
  const char *_pif_a = (a);                         \
  const char *_pif_b = (b);                         \
  _PIF_CHECK(!strcmp(_pif_a, _pif_b),                     \
             "( " #a " ) == ( " #b " )",      \
             #a, "s", _pif_a,                       \
             #b, "s", _pif_b,                       \
             NULL);                             \
  } while (0)

/* [FIXME] add the gcc null-term attribute */
void pif_check ( const char *fname,
                 int lineno,
                 int expr,
                 const char *sexpr,
                 ... );

#endif
