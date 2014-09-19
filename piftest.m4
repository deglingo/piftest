#
AC_DEFUN([AM_PATH_PIFTEST],
[
    AC_PATH_PROG([PIFTEST], [piftest], [no])
    test x"$PIFTEST" != x"no" || AC_ERROR([piftest not found])
    PKG_CHECK_MODULES([PIFTEST], [piftest])
])
# #
# AC_DEFUN([AM_PIFTEST_SUITE],
# [
#     AC_REQUIRE([AM_PATH_PIFTEST])
#     "$PIFTEST" -I $1 "$srcdir/$1/piftest.conf" || AC_ERROR(piftest -P failed)
# ])
