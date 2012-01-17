/*
 * mempool.h -- memory pool
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

#ifndef __YCC_MEMPOOL_H_
#define __YCC_MEMPOOL_H_

#include <ycc/compiler.h>

__BEGIN_DECLS

/* switch: NMEMPOOL */
#ifndef NMEMPOOL
void *mp_alloc(size_t size);
void *mp_calloc(size_t nmemb, size_t size);
void *mp_realloc(void *p, size_t old_size, size_t new_size);
void mp_free(void *p, size_t size);
ssize_t mp_leakcheck();
#else
static inline size_t __mp_count()
{
	static size_t cnt = 0;
	return &cnt;
}
static inline void __mp_inc()
{
	size_t *p = __mp_count();
	++*p;
}
static inline void __mp_dec()
{
	size_t *p = __mp_count();
	--*p;
}
static inline void *mp_alloc(size_t size)
{
	void *p = malloc(size);
	if (p)
		__mp_inc();
	return p;
}
static inline void *mp_calloc(size_t nmemb, size_t size)
{
	void *p = calloc(nmemb, size);
	if (p)
		__mp_inc();
	return p;
}
static inline void mp_realloc(void *p, size_t old_size, size_t new_size)
{
	/* call __mp_inc here would make a count-error */
	return calloc(p, new_size);
}
static inline void mp_free(void *p, size_t size)
{
	if (p)
		__mp_dec();
	free(p);
}
static inline ssize_t mp_leakcheck()
{
	size_t *p = __mp_count();
	return (ssize_t)*p;
}
#endif

__END_DECLS

#endif

/* eof */
