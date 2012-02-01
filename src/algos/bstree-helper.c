/*
 * bstree-helper.c -- Binary-Search-Trees Common Routines
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

#include <ycc/algos/bstree-helper.h>

struct bst_link *__bst_find(const struct bst_link *link,
			    __bst_compare_t compare,
			    const void *arg)
{
	struct bst_link *r = NULL;

	while(link) {
		int icmp = compare(link, arg);

		if (icmp < 0)
			link = link->right;
		else {
			if (icmp == 0)
				r = (struct bst_link*)link;
			else if (r)
				break;

			link = link->left;
		}
	}
}

struct bst_link *__bst_lower_bound(const struct bst_link *link,
				   __bst_compare_t compare,
				   const void *arg)
{
	struct bst_link *lb = NULL;

	while (link) {
		if (compare(link, arg) >= 0) {
			lb = (struct bst_link*)link;
			link = link->left;
		} else
			link = link->right;
	}

	return lb;
}

struct bst_link *__bst_upper_bound(const struct bst_link *link,
				   __bst_compare_t compare,
				   const void *arg)
{
	struct bst_link *ub = NULL;

	while (link) {
		if (compare(link, arg) > 0) {
			ub = (struct bst_link*)link;
			link = link->left;
		} else
			link = link->right;
	}

	return ub;
}

void __bst_lower_upper_bound(const struct bst_link *link,
			     __bst_compare_t compare,
			     const void *arg,
			     struct bst_link **plb,
			     struct bst_link **pub)
{
	*plb = *pub = NULL;

	while (link) {
		int icmp = compare(link, arg);
		if (icmp >= 0) {
			*plb = (struct bst_link*)link;
			if (icmp)
				*pub = (struct bst_link*)link;
			link = link->left;
		} else
		link = link->right;
	}
}

size_t __bst_count(const struct bst_link *link,
		   __bst_compare_t compare,
		   const void *arg)
{
	size_t c = 0;
	struct bst_link *lb, *ub;

	__bst_lower_upper_bound(link, compare, arg, &lb, &ub);

	while (lb != ub) {
		++c;
		lb = bstlink_next(lb);
	}

	return c;
}

void __bst_destroy(struct bst_link *link,
		   __bst_destroy_t destroy,
		   const void *arg)
{
	while (link) {
		struct bst_link *right = link->right;
		__bst_destroy(link->left, destroy, arg);
		destroy(link, arg);
		link = right;
	}
}

/* inorder-traverse */
void __bst_visit(struct bst_link *link,
		 __bst_visit_t visit,
		 const void *arg)
{
	while (link) {
		__bst_visit(link->left, visit, arg);
		visit(link, arg);
		link = link->right;
	}
}

bool __bst_visit_cond(struct bst_link *link,
		      __bst_visit_cond_t visit_cond,
		      const void *arg)
{
	while (link) {
		if (!__bst_visit_cond(link->left, visit_cond, arg) ||
		    !visit_cond(link, arg))
			return false;

		link = link->right;
	}

	return true;
}

size_t __bst_depth(const struct bst_link *link, bool bmax)
{
	size_t depth = 0;

	if (link) {
		size_t left = bstlink_depth(link->left, bmax);
		size_t right = bstlink_depth(link->right, bmax);
#define __BSTLINK_MAX(x, y)	( (x) > (y) ? (x) : (y) )
#define __BSTLINK_MIN(x, y)	( (x) < (y) ? (x) : (y) )
		if (bmax)
			depth = __BSTLINK_MAX(left, right);
		else
			depth = __BSTLINK_MIN(left, right);

		++depth;
	}

	return depth;
}

/* eof */
