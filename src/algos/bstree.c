/*
 * bstree.c -- Trival Binary Search Trees
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

#include <ycc/algos/bstree.h>

void bst_erase(struct bst_node *link, struct bst_root *bst)
{
	struct bst_node *child, *parent;

	if (!link->left || !link->right) {
		if (!link->left)
			child = link->right;
		else
			child = link->left;

		parent = link->parent;
		if (child)
			child->parent = parent;
		if (parent) {
			if (parent->left == link)
				parent->left = child;
			else
				parent->right = child;
		} else
			bst->node = child;
	} else {
		struct bst_node *scor;	/* scor: successor */
		
		scor = link->right;
		while (scor->left)
			scor = scor->left;

		if (link->parent) {
			if (link->parent->left == link)
				link->parent->left = scor;
			else
				link->parent->right = scor;
		} else
			bst->node = scor;

		child = scor->right;
		parent = scor->parent;

		if (parent == link)
			parent = scor;
		else {
			if (child)
				child->parent = parent;

			parent->left = child;
			scor->right = link->right;
			link->right->parent = scor;
		}

		scor->parent = link->parent;
		scor->left = link->left;
		link->left->parent = scor;
	}
}

/* eof */
