/*
 * rbtree.c -- Red Black Trees
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

#include <ycc/algos/rbtree.h>

void rb_insert_rebalance(struct rb_node *node, struct rb_root *rb)
{
	struct rb_node *parent, *gparent;
	struct rb_node ** const proot = &rb->node;

	/*
	 * condition
	 *	rb_color(node): RED
	 */

	/* do rebalance */
	while ((parent=node->parent) && rb_is_red(parent)) {
		gparent = parent->parent;
		if (parent == gparent->left) {
			register struct rb_node *uncle = gparent->right;

			if (uncle && rb_is_red(uncle)) {
				rb_set_black(uncle);
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}

			if (node == parent->right) {
				__BSTLINK_ROTATE_LEFT(parent, proot);
				node = parent;
				/* parent had been changed, need reset */
				parent = node->parent;	
			}

			rb_set_black(parent);
			rb_set_red(gparent);
			__BSTLINK_ROTATE_RIGHT(gparent, proot);
		} else {
			register struct rb_node *uncle = gparent->left;

			if (uncle && rb_is_red(uncle)) {
				rb_set_black(uncle);
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}

			if (node == parent->left) {
				__BSTLINK_ROTATE_RIGHT(parent, proot);
				node = parent;
				parent = node->parent;
			}

			rb_set_black(parent);
			rb_set_red(gparent);
			__BSTLINK_ROTATE_LEFT(gparent, proot);
		}
	}

	rb_set_black(*proot);
}

static inline void
__rb_erase_rebalance(struct rb_node *node,
		     struct rb_node *parent,
		     struct rb_root *rb)
{
	struct rb_node *other;
	struct rb_node **proot = &rb->node;

	while (node != *proot && (!node || rb_is_black(node))) {
		/*
		 * For here, parent have one child at least.
		 * If node is non-null, then node is black,
		 *	so sibling of node cannot be NULL.
		 * If node is null, for parent have one child at least here,
		 *	so sibling of node cannot be NULL.
		 */
		if (parent->left == node) {
			other = parent->right;
			if (rb_is_red(other)) {
				rb_set_black(other);
				rb_set_red(parent);
				__BSTLINK_ROTATE_LEFT(parent, proot);
				other = parent->right;
			}

			if ((!other->left || rb_is_black(other->left)) &&
			    (!other->right || rb_is_black(other->right))) {
				rb_set_red(other);
				node = parent;
				parent = node->parent;
			} else {
				if (!other->right ||
				    rb_is_black(other->right)) {
					rb_set_black(other->left);
					rb_set_red(other);
					__BSTLINK_ROTATE_RIGHT(other, proot);
					other = parent->right;
				}
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				/* now other->right cannot be null */
				rb_set_black(other->right);
				__BSTLINK_ROTATE_LEFT(parent, proot);
				break;
			}
		} else {
			other = parent->left;
			if (rb_is_red(other)) {
				rb_set_black(other);
				rb_set_red(parent);
				__BSTLINK_ROTATE_RIGHT(parent, proot);
				other = parent->left;
			}

			if ((!other->left || rb_is_black(other->left)) &&
			    (!other->right || rb_is_black(other->right))) {
				rb_set_red(other);
				node = parent;
				parent = node->parent;
			} else {
				if (!other->left || rb_is_black(other->left)) {
					rb_set_black(other->right);
					rb_set_red(other);
					__BSTLINK_ROTATE_LEFT(other, proot);
					other = parent->left;
				}
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->left);
				__BSTLINK_ROTATE_RIGHT(parent, proot);
				break;
			}
		}
	}

	/* force root node to BLACK */
	if (node)
		rb_set_black(node);
}

void rb_erase(struct rb_node *node, struct rb_root *rb)
{
	unsigned color;
	struct rb_node *child, *parent;

	if (!node->left || !node->right) {
		if (!node->left)
			child = node->right;
		else
			child = node->left;

		parent = node->parent;
		color = rb_color(node);
		if (child)
			child->parent = parent;

		if (parent) {
			if (parent->left == node)
				parent->left = child;
			else
				parent->right = child;
		} else
			rb->node = child;
	} else {
		struct rb_node *scor = node->right; /* scor: successor */
		while (scor->left)
			scor = scor->left;

		if (node->parent) {
			if (node->parent->left == node)
				node->parent->left = scor;
			else
				node->parent->right = scor;
		} else
			rb->node = scor;

		child = scor->right;
		parent = scor->parent;
		color = rb_color(scor);

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
		rb_set_color(scor, rb_color(node));
		node->left->parent = scor;
	}

	if (color == RB_COLOR_BLACK)
		__rb_erase_rebalance(child, parent, rb);
}

/* eof */
