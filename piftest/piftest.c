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
}



/* pif_suite_run:
 */
void pif_suite_run ( PifSuite *suite,
                     const char *path )
{
}
