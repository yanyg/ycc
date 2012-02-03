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

#include <ycc/algos/avltree.h>

void avl_insert_depth(struct avl_node *node, struct avl_root *avl)
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
__avl_erase_depth(struct avl_node *node,
		  struct avl_node *parent,
		  struct avl_root *avl)
{
	struct avl_node *other;
	struct avl_node **proot = &avl->node;

	/* empty tree */
	if (*proot)
		return;

	if (!node) {
		static struct avl_node dummy = { .depth = 0, };
		node = &dummy;
	}

	while (node != *proot && node->depth + 1 != parent->depth) {
		if (parent->left == node) {
			other = parent->right;

			if (other->depth + 1 != parent->depth) {
				--parent->depth;
				goto down;
			}

			if (other->depth - node->depth == 1)
				return;

			if (other->left->depth > other->right->depth) {
				++other->left->depth;
				--other->depth;
				__BSTLINK_ROTATE_RIGHT(other, proot);
				other = other->parent;
			}

			if (other->left && other->left->depth > node->depth) {
				--parent->depth;
				++other->depth;
			} else
				parent->depth -= 2;

			__BSTLINK_ROTATE_RIGHT(parent, proot);
			parent = other;
		} else {
			other = parent->left;

			if (other->depth + 1 != parent->depth) {
				--parent->depth;
				goto down;
			}

			if (other->depth - node->depth == 1)
				return;

			if (other->right->depth > other->left->depth) {
				++other->right->depth;
				--other->depth;
				__BSTLINK_ROTATE_LEFT(other, proot);
				other = other->parent;
			}

			if (other->right && other->right->depth > node->depth){
				--parent->depth;
				++other->depth;
			} else
				parent->depth -= 2;

			__BSTLINK_ROTATE_LEFT(parent, proot);
			parent = other;
		}

		down:
			node = parent;
			parent = parent->parent;
	}
}

void avl_erase(struct avl_node *node, struct avl_root *avl)
{
	struct avl_node *child, *parent;

	if (!node->left || !node->right) {
		if (!node->left)
			child = node->right;
		else
			child = node->left;

		parent = node->parent;
		if (child)
			child->parent = parent;

		if (parent) {
			if (parent->left == node)
				parent->left = child;
			else
				parent->right = child;
		} else
			avl->node = child;
	} else {
		struct avl_node *scor = node->right; /* scor: successor */
		while (scor->left)
			scor = scor->left;

		if (node->parent) {
			if (node->parent->left == node)
				node->parent->left = scor;
			else
				node->parent->right = scor;
		} else
			avl->node = scor;

		child = scor->right;
		parent = scor->parent;

		if (parent == node)
			parent = scor;
		else {
			if (child)
				child->parent = parent;
			parent->left = child;
			scor->right = node->right;
			node->right->parent = scor;
		}

		scor->parent = node->parent;
		scor->left = node->left;
		avl_set_depth(scor, avl_depth(node));
		node->left->parent = scor;
	}

	if (parent)
		__avl_erase_depth(child, parent, avl);
}

/* eof */
