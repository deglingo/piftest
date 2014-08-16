/* piftest.h -
 */

#ifndef _PIFTEST_H_
#define _PIFTEST_H_



typedef struct _PifSuite PifSuite;
typedef void (* PifTestFunc) ( void );

PifSuite *pif_suite_new ( const char *name );
void pif_unit_register ( const char *path );
void pif_test_register ( const char *path,
                         PifTestFunc func );
void pif_test_run ( const char *path );



#endif
