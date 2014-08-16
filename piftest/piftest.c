/* piftest.c -
 */

#include "piftest.h"

#include <stdlib.h>
#include <string.h>



/* PifSuite:
 */
struct _PifSuite
{
  char *name;
};



/* pif_suite_new:
 */
PifSuite *pif_suite_new ( const char *name )
{
  PifSuite *suite;
  suite = malloc(sizeof(PifSuite));
  suite->name = strdup(name);
  return suite;
}



/* pif_unit_register:
 */
void pif_unit_register ( const char *path )
{
}



/* pif_test_register:
 */
void pif_test_register ( const char *path,
                         PifTestFunc func )
{
}



/* pif_test_run:
 */
void pif_test_run ( const char *path )
{
}
