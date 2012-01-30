/*
 * test-rbtree.c -- Test suits of Red Black Trees
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

#include <stdio.h>
#include <stdlib.h>

#include <ycc/debug.h>

#include <ycc/algos/rbtree.h>

static int test_rbtree(size_t size);

int main(int argc, char **argv)
{
	int rtn;

	if (1 == argc)
		return test_rbtree(1024*1024);
	else {
		int i;
		for(i = 1; i < argc; ++i) {
			size_t size = (size_t)strtoul(argv[i], NULL, 10);

			rtn = test_rbtree(size);
			if (rtn)
				return rtn;
		}
	}

	return 0;
}

static int test_rbtree(size_t size)
{
	return 0;
}
