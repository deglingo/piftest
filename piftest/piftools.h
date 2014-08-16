/* piftools.h -
 */

#ifndef _PIFTOOLS_H_
#define _PIFTOOLS_H_

#include <stdio.h>
#include <stdlib.h>

#define PIF_CHECK(expr) do {                                \
    if (!(expr)) {                                          \
      fprintf(stderr, "%s:%d: test failed: `" #expr "'\n",  \
              __FILE__, __LINE__);                          \
      exit(1);                                              \
    }                                                       \
  } while (0)

#endif
