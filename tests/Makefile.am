AM_CFLAGS = -I$(top_builddir)/include

TESTS = check_polyalpha_decrypt check_input_control check_break_utils

check_PROGRAMS = check_polyalpha_decrypt check_input_control check_break_utils

check_polyalpha_decrypt_SOURCES = check_polyalpha_decrypt.c 
check_polyalpha_decrypt_CFLAGS= @CHECK_CFLAGS@ -I$(top_builddir)/include
check_polyalpha_decrypt_LDADD = @CHECK_LIBS@

check_input_control_SOURCES = check_input_control.c 
check_input_control_CFLAGS = @CHECK_CFLAGS@ -I$(top_builddir)/include
check_input_control_LDADD = @CHECK_LIBS@ $(top_builddir)/src/input_control.o

check_break_utils_SOURCES = check_break_utils.c
check_break_utils_CFLAGS = @CHECK_CFLAGS@ -I$(top_builddir)/include
check_break_utils_LDADD = @CHECK_LIBS@ $(top_builddir)/src/break_utils.o
