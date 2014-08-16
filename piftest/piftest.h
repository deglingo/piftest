/* piftest.h -
 */

#ifndef _PIFTEST_H_
#define _PIFTEST_H_



typedef struct _PifSuite PifSuite;
typedef void (* PifTestFunc) ( void );

PifSuite *pif_suite_new ( const char *name );
void pif_suite_register_unit ( PifSuite *suite,
                               const char *path );
void pif_suite_register_test ( PifSuite *suite,
                               const char *path,
                               PifTestFunc func );
void pif_suite_run ( PifSuite *suite,
                     const char *path );



#endif
