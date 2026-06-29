################################################################################
#	Name       : Makefile
#	Author     : Didier Barvaux <didier.barvaux@toulouse.viveris.com>
#	Description: create the GSE test program
################################################################################

SUBDIRS = . samples

check_PROGRAMS = \
	test_encap_deencap \
	non_regression_tests \
    non_regression_tests_no_alloc \
    cpp_sanity_test \
    cpp_asan_test

TESTS = \
	test_encap_deencap.sh \
	cpp_sanity_test \
	cpp_asan_test.sh

EXTRA_DIST = \
	encap_deencap_max_pdu_length.pcap \
	test_encap_deencap.sh \
	non_regression_tests.sh \
    non_regression_tests_no_alloc.sh \
    cpp_sanity_test.cc \
    cpp_asan_test.cc \
    cpp_asan_test.sh

AM_CPPFLAGS = \
	-I$(top_srcdir)/src/common \
	-I$(top_srcdir)/src/encap \
	-I$(top_srcdir)/src/deencap

AM_LDFLAGS = -L$(top_srcdir)/src/

test_encap_deencap_SOURCES = test_encap_deencap.c
test_encap_deencap_LDADD = \
	$(top_builddir)/src/libgse.la \
	-lpcap 

non_regression_tests_SOURCES = non_regression_tests.c
non_regression_tests_LDADD = \
	$(top_builddir)/src/libgse.la \
	-lpcap

non_regression_tests_no_alloc_SOURCES = non_regression_tests_no_alloc.c
non_regression_tests_no_alloc_LDADD = \
   $(top_builddir)/src/libgse.la \
   -lpcap

cpp_sanity_test_SOURCES = cpp_sanity_test.cc
cpp_sanity_test_LDADD = $(top_builddir)/src/libgse.la

cpp_asan_test_SOURCES = cpp_asan_test.cc
cpp_asan_test_LDADD = $(top_builddir)/src/libgse.la
cpp_asan_test_CXXFLAGS = $(AM_CXXFLAGS) -fsanitize=address,undefined -fno-omit-frame-pointer
cpp_asan_test_LDFLAGS = $(AM_LDFLAGS) -fsanitize=address,undefined
