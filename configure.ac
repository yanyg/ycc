#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([ycc], [1.0.0], [cppgp@qq.com], [ycc], [http://cppgp.blog.com])
AC_COPYRIGHT([GPLv2])
AC_REVISION([$Revision: 1.0 $])
AC_CONFIG_AUX_DIR([srcdir/../config])
AC_CONFIG_SRCDIR([src/include/ycc/mempool.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
