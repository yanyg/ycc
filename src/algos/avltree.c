/*
 * avltree.c -- Self-balancing Binary Search Trees
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

#include <ycc/algos/avltree.h>

void avl_insert_rebalance(struct avl_node *node, struct avl_root *avl)
{
	struct avl_node *parent, *gparent;
	struct avl_node ** const proot = &avl->node;

	/* do rebalance */
	while ((parent=node->parent) && node->depth == parent->depth) {
		++parent->depth;

		if (!(gparent=parent->parent))
			break;

		if (parent == gparent->left) {
			register struct avl_node *uncle = gparent->right;

			if ((uncle && parent->depth - uncle->depth > 1) ||
			    !uncle) {
				if (node == parent->right) {
					++node->depth;
					--parent->depth;
					__BSTLINK_ROTATE_LEFT(parent, proot);
				}

				--gparent->depth;
				__BSTLINK_ROTATE_RIGHT(gparent, proot);
			}
			else
				node = parent;
		} else {
			register struct avl_node *uncle = gparent->left;

			if ((uncle && parent->depth - uncle->depth > 1) ||
			    !uncle) {
				if (node == parent->left) {
					++node->depth;
					--parent->depth;
					__BSTLINK_ROTATE_RIGHT(parent, proot);
				}

				--gparent->depth;
				__BSTLINK_ROTATE_LEFT(gparent, proot);
			}
			else
				node = parent;
		}
	}
}

static inline void
__avl_erase_rebalance(struct avl_node *node,
		      struct avl_node *parent,
		      struct avl_node **proot)
{
	struct avl_node *other;

	/* empty tree */
	assert(parent);

	while (node != *proot) {
		unsigned depth = node ? node->depth : 1;

		if (depth + 1 == parent->depth)
			return;

		if (parent->left == node) {
			other = parent->right;

			if (other->depth + 1 != parent->depth) {
				--parent->depth;
				goto down;
			}

			if (other->depth == depth + 1)
				return;

			if (other->left &&
			    (!other->right ||
			     other->left->depth > other->right->depth)) {
				++other->left->depth;
				--other->depth;
				__BSTLINK_ROTATE_RIGHT(other, proot);
				other = other->parent;
			}

			if (other->left && other->left->depth > depth) {
				--parent->depth;
				++other->depth;
			} else
				parent->depth -= 2;

			__BSTLINK_ROTATE_LEFT(parent, proot);
			parent = other;
		} else {
			other = parent->left;

			if (other->depth + 1 != parent->depth) {
				--parent->depth;
				goto down;
			}

			if (other->depth == depth + 1)
				return;

			if (other->right &&
			    (!other->left ||
			     other->right->depth > other->left->depth)) {
					++other->right->depth;
					--other->depth;
					__BSTLINK_ROTATE_LEFT(other, proot);
					other = other->parent;
			}

			if (other->right && other->right->depth > depth) {
				--parent->depth;
				++other->depth;
			} else
				parent->depth -= 2;

			__BSTLINK_ROTATE_RIGHT(parent, proot);
			parent = other;
		}

		down:
			node = parent;
			parent = parent->parent;
	}
}

/* erase specialized */
#define __BSTLINK_TYPE struct avl_node
#define __BSTLINK_ERASE_SPECIALIZE_BOTH(node, scor)		\
	avl_set_depth(scor, avl_depth(node))
#define __BSTLINK_ERASE_SPECIALIZE_DO(child, parent, proot)	\
	if (parent)						\
		__avl_erase_rebalance(child, parent, proot);

#include "bstree-internal.h"
void avl_erase(struct avl_node *node, struct avl_root *avl)
{
	__BSTLINK_ERASE(node, &avl->node);
}

#ifndef NDEBUG
static bool __avl_valid(struct avl_node *root, size_t depth)
{
}

bool avl_isvalid(struct avl_root *avl)
{
	size_t depth = 1;
	return __avl_valid(avl->node, depth);
}
#endif

/* eof */
