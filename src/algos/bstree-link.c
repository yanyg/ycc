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

/* eof */
