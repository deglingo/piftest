#

TESTS = piftest-test

check_PROGRAMS = piftest-test

piftest_test_CFLAGS = -I$(top_srcdir)/piftest

piftest_test_LDFLAGS = -L$(top_builddir)/piftest -lpiftest

piftest_test_SOURCES = \
	piftest-test.c \
	test_base.c

BUILT_SOURCES = $(piftest_test_SOURCES)

-include piftest-test.mk

piftest-test.mk:
	$(top_builddir)/bin/piftest -M
