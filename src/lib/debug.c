/*
 * debug.c -- debug macros, routines, etc.
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

#include <assert.h>
#include <time.h>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <ycc/dstdio.h>

static bool bstamp = true;

bool dstamp(bool x)
{
	bool r = bstamp;
	bstamp = x;
	return r;
}

void __dvfprintf(FILE *stream,
	      const char *file,
	      const char *func,
	      size_t line,
	      const char *fmt,
	      va_list ap)
{
	if(bstamp)
		(void)fprintf(stream, "%s, %zu, %s: ", file, line, func);

	vfprintf(stream, fmt, ap);
}

/* eof */
