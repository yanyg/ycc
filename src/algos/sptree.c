/*
 * sptree.c -- Splay Trees
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

#include <ycc/algos/sptree.h>

void __spt_splay(struct spt_node *node, struct spt_root *spt)
{
	struct spt_node **proot = &spt->node;

	while (node != *proot) {
		struct spt_node *parent = node->parent;
		struct spt_node *gparent = parent->parent;

		if (node == parent->left) {
			if (!gparent) {
				__BSTLINK_ROTATE_RIGHT(parent, proot);
				continue;
			}

			if (parent == gparent->left) {
				__BSTLINK_ROTATE_RIGHT(gparent, proot);
				__BSTLINK_ROTATE_RIGHT(parent, proot);
			} else {
				__BSTLINK_ROTATE_RIGHT(parent, proot);
				__BSTLINK_ROTATE_LEFT(gparent, proot);
			}
		} else {
			if (!gparent) {
				__BSTLINK_ROTATE_LEFT(parent, proot);
				continue;
			}

			if (parent == gparent->right) {
				__BSTLINK_ROTATE_LEFT(gparent, proot);
				__BSTLINK_ROTATE_LEFT(parent, proot);
			} else {
				__BSTLINK_ROTATE_LEFT(parent, proot);
				__BSTLINK_ROTATE_RIGHT(gparent, proot);
			}
		}
	}
}

void spt_erase(struct spt_node *node, struct spt_root *spt)
{
	struct spt_node *child, *parent;

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
			spt->node = child;
	} else {
		struct spt_node *scor = node->right; /* scor: successor */
		while (scor->left)
			scor = scor->left;

		if (node->parent) {
			if (node->parent->left == node)
				node->parent->left = scor;
			else
				node->parent->right = scor;
		} else
			spt->node = scor;

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
		node->left->parent = scor;
	}

	if (parent)
		__spt_splay(parent, spt);
}

/* eof */
