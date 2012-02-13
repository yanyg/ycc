#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([ycc], [1.0.0], [cppgp@qq.com], [ycc], [http://cppgp.blog.com])
AC_CONFIG_COMMANDS_PRE([echo top_srcdir=$top_srcdir])
AC_CONFIG_AUX_DIR([build-aux])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
LT_INIT
AC_COPYRIGHT([GPLv2])
AC_REVISION([$Revision: 1.0 $])
AC_CONFIG_SRCDIR([src/include/ycc/mempool.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h	\
		  limits.h	\
		  netinet/in.h	\
		  stddef.h	\
		  stdlib.h	\
		  string.h	\
		  sys/socket.h	\
		  sys/time.h	\
		  unistd.h	\
		  ])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset select socket])

AC_CONFIG_FILES([Makefile
		 src/Makefile
		 src/algos/Makefile
		 src/lib/Makefile
		 src/net/Makefile
		 src/tests/Makefile
		 src/tests/algos/Makefile
		 ])
AC_OUTPUT
