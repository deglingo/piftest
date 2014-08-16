AC_INIT([piftest], [0.0.0])
AM_INIT_AUTOMAKE

# [fixme] check for python3
AC_SUBST(PYTHON)
AC_MSG_CHECKING([for python3])
if PYTHON=`which python3`; then
    AC_MSG_RESULT([$PYTHON])
else
    AC_MSG_RESULT([no])
    AC_ERROR([python3 not found])
fi

AC_CONFIG_FILES([ \
  Makefile \
  bin/Makefile \
  test/Makefile \
])
AC_CONFIG_FILES([bin/piftest], [chmod +x bin/piftest])
AC_CONFIG_FILES([test/piftest.conf])
AC_OUTPUT
