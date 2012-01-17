/*
 * debug.h -- debug macros, routines, etc.
 *
 * Copyright (C) 2012-2013 yanyg (cppgp@qq.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING, if not see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef __YCC_DSTDIO_H_
#define __YCC_DSTDIO_H_

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#include <ycc/compiler.h>

__BEGIN_DECLS

bool dstamp(bool stamp);
#ifdef NDEBUG
/* NDEBUG: turn off */
#define DINSERT(x)			__ASSERT_VOID_CAST(0)
#define dprintf(fmt)			__ASSERT_VOID_CAST(0)
#define dfprintf(stream, fmt)		__ASSERT_VOID_CAST(0)
#define dvprintf(fmt, ap)		__ASSERT_VOID_CAST(0)
#define dvfprintf(stream, fmt, ap)	__ASSERT_VOID_CAST(0)
#else
#define DINSERT(x)			x
#define  dprintf(fmt, ...)		__dvprintf(			\
	stdout, __FILE__, __func__, __LINE__, (fmt), ## __VA_ARGS__)
#define  dfprintf(stream, fmt, ...)	__dvprintf(			\
	(stream), __FILE__, __func__, __LINE__, (fmt), ## __VA_ARGS__)
#define  dvprintf(fmt, ap)	__dvfprintf(				\
	stdout, __FILE__, __func__, __LINE__, (fmt), (ap))
#define  dvfprintf(stream, fmt, ap)	__dvfprintf(			\
	(stream), __FILE__, __func__, __LINE__, (fmt), (ap))

void __dvfprintf(FILE *stream,
	      const char *file,
	      const char *func,
	      size_t line,
	      const char *fmt,
	      va_list ap);
static inline void __dvprintf(FILE *stream,
			    const char *file,
			    const char *func,
			    size_t line,
			    const char *fmt,
			    ...)
{
	va_list ap;

	va_start(ap, fmt);
	__dvfprintf(stream, file, func, line, fmt, ap);
	va_end(ap);
}
#endif

__END_DECLS

#endif

/* eof */
