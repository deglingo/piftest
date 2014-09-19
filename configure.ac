AC_INIT([piftest], [0.0.0])
AM_INIT_AUTOMAKE

# fix default CFLAGS
: ${CFLAGS:=-g -Wall}

# define some dirs
AC_SUBST([aclocaldir], ['${datadir}/aclocal'])
AC_SUBST([pkgconfigdir], '${libdir}/pkgconfig')

AC_PROG_CC
AM_PROG_CC_C_O
LT_INIT

# [fixme] check for python3
AC_SUBST(PYTHON)
AC_MSG_CHECKING([for python3])
if PYTHON=`which python3`; then
    AC_MSG_RESULT([$PYTHON])
else
    AC_MSG_RESULT([no])
    AC_ERROR([python3 not found])
fi

# [fixme]
AC_SUBST([PIFTEST], ['$(abs_top_builddir)/bin/piftest'])
AC_SUBST([PIFTEST_DEPS], ['$(abs_top_builddir)/bin/piftest'])
dnl test -d test/.deps || mkdir -vp test/.deps
dnl for n in piftest-test test_base test_data test_setup test_tools test_lib; do
dnl     f="test/.deps/$n.Po"
dnl     test -e "$f" || echo "$n.o: $n.c" >"$f"
dnl done

# the test suite modules must be defined here so we can generate the
# .Po files at configure time
m4_define([piftest_test_modules], [ \
  test_base \
  test_data \
  test_setup \
  test_unit \
  test_tools \
  test_lib \
])
AC_SUBST([PIFTEST_TEST_MODULES], 'm4_map_args_w(piftest_test_modules, [], [], [ ])')
mkdir -vp test/.deps
for mod in piftest-test $PIFTEST_TEST_MODULES; do
    echo "creating test/.deps/$mod.Po"
    echo "$mod.o: $mod.c" >test/.deps/$mod.Po
done

AC_CONFIG_FILES([ \
  Makefile \
  bin/Makefile \
  piftest/Makefile \
  test/Makefile \
])
AC_CONFIG_FILES([piftest.pc])
AC_CONFIG_FILES([bin/piftest], [chmod +x bin/piftest])
AC_OUTPUT
