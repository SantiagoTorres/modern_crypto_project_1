## src-specific makefile
# AM_LDFLAGS = -lwhatever
AM_CFLAGS = -I$(top_builddir)/include

# If we want to make a linked library because we can
# lib_LTLIBRARIES = libpolypasswordhasher.la
# libpolypasswordhasher_la_SOURCES = main.c\
# libpolypasswordhasher_la_LIBADD = $(top_builddir)/lib/libgfshare.la
	

bin_PROGRAMS = polyalpha_decrypt
polyalpha_decrypt_SOURCES = polyalpha_decrypt.c input_control.c
polyalpha_decrypt_CFLAGS = -I$(top_builddir)/include/

#polyalpha_decrypt_LDADD = $(top_builddir)/src/libpolypasswordhasher.la
