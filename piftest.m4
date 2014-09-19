#
AC_DEFUN([AM_PATH_PIFTEST],
[
    AC_PATH_PROG([PIFTEST], [piftest], [no])
    test x"$PIFTEST" != x"no" || AC_ERROR([piftest not found])
    PKG_CHECK_MODULES([PIFTEST], [piftest])
])
#
AC_DEFUN([AM_PIFTEST_SUITE],
[
    AC_REQUIRE([AM_PATH_PIFTEST])
    AC_CONFIG_FILES(
        [$1/piftest.conf],
        [(cd $1 && $PIFTEST -P)],
        [PIFTEST="$PIFTEST"])
])
