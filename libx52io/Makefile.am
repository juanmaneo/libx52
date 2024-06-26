# Automake for libx52io
#
# Copyright (C) 2012-2020 Nirenjan Krishnan (nirenjan@nirenjan.org)
#
# SPDX-License-Identifier: GPL-2.0-only WITH Classpath-exception-2.0

lib_LTLIBRARIES += libx52io.la

# X52 IO library
# This library handles the HID parsing of the X52 USB reports
# Libtool Version Info
# See: https://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
libx52io_v_CUR=1
libx52io_v_AGE=0
libx52io_v_REV=0
libx52io_la_SOURCES = \
	libx52io/io_core.c \
	libx52io/io_axis.c \
	libx52io/io_parser.c \
	libx52io/io_strings.c \
	libx52io/io_device.c
libx52io_la_CFLAGS = @HIDAPI_CFLAGS@ -DLOCALEDIR=\"$(localedir)\" -I $(top_srcdir) $(WARN_CFLAGS)
libx52io_la_LDFLAGS = \
	-export-symbols-regex '^libx52io_' \
	-version-info $(libx52io_v_CUR):$(libx52io_v_REV):$(libx52io_v_AGE) @HIDAPI_LIBS@ \
	$(WARN_LDFLAGS)
libx52io_la_LIBADD = @LTLIBINTL@

# Header files that need to be copied
x52include_HEADERS += libx52io/libx52io.h

# pkg-config files
pkgconfig_DATA += libx52io/libx52io.pc

if HAVE_CMOCKA
TESTS += test-axis test-parser
check_PROGRAMS += test-axis test-parser

test_axis_SOURCES = libx52io/test_axis.c $(libx52io_la_SOURCES)
test_axis_CFLAGS = @CMOCKA_CFLAGS@ $(libx52io_la_CFLAGS)
test_axis_LDFLAGS = @CMOCKA_LIBS@ @HIDAPI_LIBS@ $(WARN_LDFLAGS)
test_axis_LDADD = @LTLIBINTL@

test_parser_SOURCES = libx52io/test_parser.c $(libx52io_la_SOURCES)
test_parser_CFLAGS = @CMOCKA_CFLAGS@ $(libx52io_la_CFLAGS)
test_parser_LDFLAGS = @CMOCKA_LIBS@ @HIDAPI_LIBS@ $(WARN_LDFLAGS)
test_parser_LDADD = @LTLIBINTL@

# Add a dependency on test_parser_tests.c
libx52io/test_parser.c: libx52io/test_parser_tests.c
endif

# Extra files that need to be in the distribution
EXTRA_DIST += \
	libx52io/libx52io.h \
	libx52io/io_common.h \
	libx52io/test_parser_tests.c
