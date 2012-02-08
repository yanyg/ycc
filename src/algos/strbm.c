/*
 * strbm.c -- Exact String Matching: Boyer-Moore [BM 77]
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

/*
 * [BM 77] A fast string search algorithm,
 *         R. S. Boyer and J. S. Moore,
 *         Comm. ACM, 20, 1977, pp. 762–772.
 */

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>

#include <ycc/algos/string.h>

void strbm_init(const char *needle, size_t n,
		size_t *table_sgs, size_t *table_ebc)
{
	/*
	 * sgs: strong good suffix
	 * ebc: extended bad character
	 */

	size_t i, j, k;
	size_t *sgs = table_sgs + 1, *backup = sgs + n;

	memset(sgs, 0, n*sizeof(*sgs));

	/* suffix */
	i = n - 1;
	j = n;
	while ((size_t)-1 != i) {
		backup[i] = j;

		while (j < n && needle[i] != needle[j]) {
			if (!sgs[j])
				sgs[j] = j - i;

			j = backup[j];
		}

		--i;
		--j;
	}

	/* prefix */
	k = j + 1;
	for (i = 0; i < k; ++i)
		if (!sgs[i])
			sgs[i] = k;

	i = backup[j];
	while (j < n) {
		while (j < i) {
			if (!sgs[j])
				sgs[j] = i;
			++j;
		}
		i = backup[i];
	}

	/* ebc ... */
	strbmh_init(needle, n, table_ebc);
}

char *strbm_find(const char *haystack, const char *needle,
		 size_t h, size_t n,
		 const size_t *table_sgs, const size_t *table_ebc)
{
	size_t i, j, n1 = n - 1;

	if (!n)
		return (char*)haystack;

	while (h > n1) {
		for (i = n1; i != (size_t)-1 && haystack[i] == needle[i]; --i);

		if (i == (size_t)-1)	/* [0, n1] are equal. */
			return (char*)haystack;

		if (table_sgs[i] > table_ebc[(u_char)haystack[n1]])
			j = table_sgs[i];
		else
			j = table_ebc[(u_char)haystack[n1]];
		h -= j;
		haystack += j;
	}

	return NULL;
}

/* eof */
