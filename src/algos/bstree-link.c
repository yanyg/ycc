/*
 * bstree-link.c -- Binary-Search-Trees Common Routines
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
#include <stddef.h>

#include <ycc/algos/bstree-link.h>

/*
 * bstlink_rotate_left
 *
 *  Illustration
 *      |               |
 *      X               Y
 *     / \             / \
 *    T1  Y  ---->    X   T3
 *       / \         / \
 *      T2 T3      T1  T2
 *
 *  Prerequisites
 *    X and Y(the right child of X) MUST not be NULL
 *    T1, T2, and T3 are subtrees which can be empty or non-empty
 */
void bstlink_rotate_left(struct bst_link *link, struct bst_link **proot)
{
	struct bst_link *right, *parent;

	assert(link);
	assert(proot);
	assert(link->right);

	right = link->right;
	parent = link->parent;

	if ((link->right = right->left))
		right->left->parent = link;
	right->left = link;

	right->parent = parent;

	if (parent) {
		if (link == parent->left)
			parent->left = right;
		else
			parent->right = right;
	} else
		*proot = right;

	link->parent = right;
}

/*
 * bstlink_rotate_right
 *
 *  Illustration
 *        |            |
 *        X            Y
 *       / \          / \
 *      Y  T1  --->  T2  X
 *     / \              / \
 *    T2 T3            T3  T1
 *
 *  Prerequisites
 *    X and Y(the left child of X) MUST not be NULL
 *    T1, T2, and T3 are subtrees which can be empty or non-empty
 *
 */
void bstlink_rotate_right(struct bst_link *link, struct bst_link **proot)
{
	struct bst_link *left, *parent;

	assert(link);
	assert(proot);
	assert(link->left);

	left = link->left;
	parent = link->parent;

	if ((link->left=left->right))
		left->right->parent = link;
	left->right = link;

	left->parent = parent;

	if (parent) {
		if (link == parent->right)
			parent->right = left;
		else
			parent->left = left;
	} else
		*proot = left;

	link->parent = left;
}

struct bst_link *bstlink_first(const struct bst_link *link)
{
	if (!link)
		return NULL;

	while (link->left)
		link = link->left;

	return (struct bst_link*)link;
}

struct bst_link *bstlink_last(const struct bst_link *link)
{
	if (!link)
		return NULL;

	while (link->right)
		link = link->right;

	return (struct bst_link*)link;
}

struct bst_link *bstlink_next(const struct bst_link *link)
{
	struct bst_link *parent;

	/*
	 * If we have a right-child, go down and then
	 * left as far as we can.
	 */
	if (link->right) {
		link = link->right;
		while (link->left)
			link = link->left;
		return (struct bst_link*)link;
	}

	/*
	 * No right-child, go up and find the first ancestor
	 * which right-subtree does not include link.
	 * Otherwise return NULL.
	 */
	while ((parent=link->parent) && link == parent->right)
		link = parent;

	return (struct bst_link*)parent;
}

struct bst_link *bstlink_prev(const struct bst_link *link)
{
	struct bst_link *parent;

	/*
	 * If we have a left-child, go down and then
	 * right as far as we can.
	 */
	if (link->left) {
		link = link->left;
		while (link->right)
			link = link->right;

		return (struct bst_link*)link;
	}

	/*
	 * No right-child, go up and find the first ancestor
	 * which left-subtree does not include link.
	 * Otherwise return NULL.
	 */
	while ((parent=link->parent) && link == parent->left)
		link = parent;

	return (struct bst_link*)parent;
}

struct bst_link *bstlink_lower_bound(const struct bst_link *link,
				     bstlink_compare_t compare,
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

struct bst_link *bstlink_upper_bound(const struct bst_link *link,
				     bstlink_compare_t compare,
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

void bstlink_lower_upper_bound(const struct bst_link *link,
			       bstlink_compare_t compare,
			       const void *arg,
			       struct bst_link **plower,
			       struct bst_link **pupper)
{
	int icmp;
	*plower = *pupper = NULL;

	while (link) {
		icmp = compare(link, arg);
		if (icmp >= 0) {
			if (icmp)
				*pupper = (struct bst_link*)link;
			*plower = (struct bst_link*)link;
			link = link->left;
		} else
			link = link->right;
	}
}

size_t bstlink_count(const struct bst_link *link,
				     bstlink_compare_t compare,
				     const void *arg)
{
	size_t count = 0;
	const struct bst_link *lb = bstlink_lower_bound(link, compare, arg);
	const struct bst_link *ub = bstlink_upper_bound(link, compare, arg);

	while (lb != ub) {
		++count;
		lb = bstlink_next(lb);
	}

	return count;
}

void bstlink_destroy(struct bst_link *link,
		     bstlink_destroy_t destroy,
		     const void *arg)
{
	while (link) {
		struct bst_link *left = link->left;
		bstlink_destroy(link->right, destroy, arg);
		destroy(link, arg);
		link = left;
	}
}

void bstlink_visit(struct bst_link *link,
		   bstlink_visit_t visit,
		   const void *arg)
{
	while (link) {
		bstlink_visit(link->left, visit, arg);
		visit(link, arg);
		link = link->right;
	}
}

bool bstlink_visit_cond(struct bst_link *link,
		   bstlink_visit_cond_t visit_cond,
		   const void *arg)
{
	while (link) {
		if (!bstlink_visit_cond(link->left, visit_cond, arg) ||
		    !visit_cond(link, arg))
			return false;

		link = link->right;
	}

	return true;
}

/* eof */
