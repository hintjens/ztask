#################################################################
#   GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY    #
#   Please read the README.txt file in the model directory.     #
#################################################################
lib_LTLIBRARIES = libztask.la

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libztask.pc

include_HEADERS = \
    ../include/ztask_classes.h \
    ../include/ztask.h \
    ../include/ztask_mon.h \
    ../include/ztask_mon_proc.h \
    ../include/ztask_utils.h

libztask_la_SOURCES = \
    platform.h \
    ztask.c \
    ztask_mon.c \
    ztask_mon_proc.c \
    ztask_utils.c


AM_CFLAGS = -g
AM_CPPFLAGS = -I$(top_srcdir)/include
bin_PROGRAMS = ztask_selftest
ztask_selftest_LDADD = libztask.la
ztask_selftest_SOURCES = ztask_selftest.c

if ON_MINGW
libztask_la_LDFLAGS = -no-undefined -avoid-version -version-info @LTVER@
else
libztask_la_LDFLAGS = -version-info @LTVER@
endif

TESTS = ztask_selftest

#################################################################
#   GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY    #
#   Please read the README.txt file in the model directory.     #
#################################################################
