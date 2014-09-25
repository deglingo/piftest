/* piftools.h -
 */

#ifndef _PIFTOOLS_H_
#define _PIFTOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _PIF_CHECK(expr, sexpr, values...)      \
  pif_check(__FILE__, __LINE__,                 \
            (expr), sexpr, values)

#define PIF_CHECK(expr) do {                    \
    int _pif_expr = (expr) ? 1 : 0;             \
    _PIF_CHECK(_pif_expr,                       \
               #expr,                           \
               #expr, "i", _pif_expr,           \
               NULL);                           \
  } while (0)

#define PIF_CHECK_EQ(a, b) do {                 \
    int _pif_a = (a);                           \
    int _pif_b = (b);                           \
    _PIF_CHECK(_pif_a == _pif_b,                \
               "( " #a " ) == ( " #b " )",      \
               #a, "i", _pif_a,                 \
               #b, "i", _pif_b,                 \
               NULL);                           \
  } while (0)

#define PIF_CHECK_EQ_STR(a, b) do {           \
  const char *_pif_a = (a);                         \
  const char *_pif_b = (b);                         \
  _PIF_CHECK(!strcmp(_pif_a, _pif_b),                     \
             "( " #a " ) == ( " #b " )",      \
             #a, "s", _pif_a,                       \
             #b, "s", _pif_b,                       \
             NULL);                             \
  } while (0)

#define PIF_CHECK_EQ_PTR(a, b) do {             \
    void *_pif_a = (void *) (a);                \
    void *_pif_b = (void *) (b);                \
    _PIF_CHECK(_pif_a == _pif_b,                \
               "( " #a " ) == ( " #b " ) ",     \
               #a, "p", _pif_a,                 \
               #b, "p", _pif_b,                 \
               NULL);                           \
  } while (0)

/* [FIXME] add the gcc null-term attribute */
void pif_check ( const char *fname,
                 int lineno,
                 int expr,
                 const char *sexpr,
                 ... );

#endif
