/* piftest.h -
 */

#ifndef _PIFTEST_H_
#define _PIFTEST_H_



typedef void (* PifTestFunc) ( void );

void pif_unit_register ( const char *path );
void pif_test_register ( const char *path,
                         PifTestFunc func );



#endif
