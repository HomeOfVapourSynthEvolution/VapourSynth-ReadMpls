warning_flags = -Wall -Wextra -Wshadow -Wno-unused-parameter
common_cflags = -O3 $(MFLAGS) $(warning_flags)
AM_CXXFLAGS = -std=c++11 $(common_cflags)

AM_CPPFLAGS = $(VapourSynth_CFLAGS) $(LIBBLURAY_CFLAGS)

lib_LTLIBRARIES = libreadmpls.la

libreadmpls_la_SOURCES = ReadMpls/ReadMpls.cpp

libreadmpls_la_LIBADD = $(LIBBLURAY_LIBS)

libreadmpls_la_LDFLAGS = -no-undefined -avoid-version $(PLUGINLDFLAGS)
