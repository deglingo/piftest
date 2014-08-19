#

TESTS = piftest-test

check_PROGRAMS = piftest-test

piftest_test_SOURCES = \
	piftest-test.c \
	test_base.c

BUILT_SOURCES = $(piftest_test_SOURCES)

$(piftest_test_SOURCES) : piftest-test.stamp-h

piftest-test.stamp-h: piftest.conf $(top_builddir)/bin/piftest
	$(top_builddir)/bin/piftest -G
	echo >$@
