#
AC_DEFUN([AM_PATH_PIFTEST],
[
    AC_PATH_PROG([PIFTEST], [piftest], [no])
    test x"$PIFTEST" != x"no" || AC_ERROR([piftest not found])
])
# #
AC_DEFUN([AM_PIFTEST_SUITE],
[
    AC_REQUIRE([AM_PATH_PIFTEST])
    # "$PIFTEST" -P $1 || AC_ERROR(piftest -P failed)
])
