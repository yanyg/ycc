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

static inline bool
__avl_insert(struct avl_node *node,
	    struct avl_root *avl,
	    int (*compare_link)(const struct avl_node *node1,
				const struct avl_node *node2,
				const void *arg),
	    const void *arg,
	    bool bunique)
{
	int icmp;
	struct avl_node *parent = NULL;
	struct avl_node **pnode = &avl->node;

	while (*pnode) {
		parent = *pnode;
		icmp = compare_link(*pnode, node, arg);

		if (icmp > 0)
			pnode = &(*pnode)->left;
		else {
			/* For bunique == true,
			 * if avltree had have a node which value equals to
			 * the insert-node, the insert-operation fail.
			 */
			 if (!icmp && bunique)
				 return false;

			pnode = &(*pnode)->right;
		}
	}

	avl_link_node(node, parent, pnode);
	avl_insert_depth(node, avl);

	return true;
}

void avl_insert(struct avl_node *node,
	       struct avl_root *avl,
	       int (*compare_link)(const struct avl_node *node1,
				   const struct avl_node *node2,
				   const void *arg),
	       const void *arg)
{
	(void)__avl_insert(node, avl, compare_link, arg, false);
}

bool avl_insert_unique(struct avl_node *node,
	       struct avl_root *avl,
	       int (*compare_link)(const struct avl_node *node1,
				   const struct avl_node *node2,
				   const void *arg),
	       const void *arg)
{
	return __avl_insert(node, avl, compare_link, arg, true);
}

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
					__bstlink_rotate_left(parent, proot);
				}

				--gparent->depth;
				__bstlink_rotate_right(gparent, proot);
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
					__bstlink_rotate_right(parent, proot);
				}

				--gparent->depth;
				__bstlink_rotate_left(gparent, proot);
			}
			else
				node = parent;
		}
	}
}

static inline void __avl_erase_depth(struct avl_node *node,
				    struct avl_node *parent,
				    struct avl_root *avl)
{
	struct avl_node *other;
	struct avl_node **proot = &avl->node;

	while (node != *proot && (!node || avl_is_black(node))) {
		/*
		 * For here, parent have one child at least.
		 * If node is non-null, then node is black,
		 *	so sibling of node cannot be NULL.
		 * If node is null, for parent have one child at least here,
		 *	so sibling of node cannot be NULL.
		 */
		if (parent->left == node) {
			other = parent->right;
			if (avl_is_red(other)) {
				avl_set_black(other);
				avl_set_red(parent);
				__bstlink_rotate_left(parent, proot);
				other = parent->right;
			}

			if ((!other->left || avl_is_black(other->left)) &&
			    (!other->right || avl_is_black(other->right))) {
				avl_set_red(other);
				node = parent;
				parent = node->parent;
			} else {
				if (!other->right ||
				    avl_is_black(other->right)) {
					avl_set_black(other->left);
					avl_set_red(other);
					__bstlink_rotate_right(other, proot);
					other = parent->right;
				}
				avl_set_color(other, avl_color(parent));
				avl_set_black(parent);
				/* now other->right cannot be null */
				avl_set_black(other->right);
				__bstlink_rotate_left(parent, proot);
				break;
			}
		} else {
			other = parent->left;
			if (avl_is_red(other)) {
				avl_set_black(other);
				avl_set_red(parent);
				__bstlink_rotate_right(parent, proot);
				other = parent->left;
			}

			if ((!other->left || avl_is_black(other->left)) &&
			    (!other->right || avl_is_black(other->right))) {
				avl_set_red(other);
				node = parent;
				parent = node->parent;
			} else {
				if (!other->left || avl_is_black(other->left)) {
					avl_set_black(other->right);
					avl_set_red(other);
					__bstlink_rotate_left(other, proot);
					other = parent->left;
				}
				avl_set_color(other, avl_color(parent));
				avl_set_black(parent);
				avl_set_black(other->left);
				__bstlink_rotate_right(parent, proot);
				break;
			}
		}
	}

	/* force root node to BLACK */
	if (node)
		avl_set_black(node);
}

void avl_erase(struct avl_node *node, struct avl_root *avl)
{
	unsigned color;
	struct avl_node *child, *parent;

	if (!node->left || !node->right) {
		if (!node->left)
			child = node->right;
		else
			child = node->left;

		parent = node->parent;
		color = avl_color(node);
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
		color = avl_color(scor);

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
		avl_set_color(scor, avl_color(node));
		node->left->parent = scor;
	}

	if (color == avl_COLOR_BLACK)
		__avl_erase_depth(child, parent, avl);
}

void avl_erase_range(struct avl_node *beg,
		    struct avl_node *end,
		    struct avl_root *avl)
{
	struct avl_node *del;

	while (beg != end) {
		del = beg;
		beg = avl_next(beg);
		avl_erase(del, avl);
	}
}

void
avl_erase_equal(struct avl_root *avl,
	       int (*compare)(const struct avl_node *node, const void *arg),
	       void (*destroy)(struct avl_node *node, const void *arg),
	       const void *arg_compare,
	       const void *arg_destroy)
{
	struct avl_node *beg, *end, *del;

	avl_lower_upper_bound(avl, compare, arg_compare, &beg, &end);

	while (beg != end) {
		del = beg;
		beg = avl_next(beg);
		avl_erase(del, avl);
		destroy(del, arg_destroy);
	}
}

/* eof */
