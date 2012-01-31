/*
 * bstree-link.h -- Binary-Search-Trees Common Routines
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

/*
 * You always need not to include this file directly.
 * This file is designed to provide basic binary search tree routines,
 * And the interface is volatile 
 */

#ifndef __YCALGOS_BSTREE_LINK_H_
#define __YCALGOS_BSTREE_LINK_H_

#include <stddef.h>
#include <stdbool.h>

#include <ycc/compiler.h>

__BEGIN_DECLS

/* bstlink: Binary Search Tree Link */
#define __BST_LINK_MEMBER(type)	\
	type *parent, *left, *right
struct bst_link
{
	__BST_LINK_MEMBER(struct bst_link);
}__aligned(sizeof(void*));

void bstlink_rotate_left(struct bst_link *link, struct bst_link **pproot);
void bstlink_rotate_right(struct bst_link *link, struct bst_link **proot);

struct bst_link *bstlink_first(const struct bst_link *link);
struct bst_link *bstlink_last(const struct bst_link *link);
struct bst_link *bstlink_next(const struct bst_link *link);
struct bst_link *bstlink_prev(const struct bst_link *link);

static inline void bstlink_init(struct bst_link *link,
				struct bst_link *parent,
				struct bst_link **plink)
{
	link->parent = parent;
	link->left = link->right = NULL;
	*plink = link;
}

#define __bstlink_rotate_left(link, pproot)				\
		bstlink_rotate_left					\
		(							\
			(struct bst_link*)link,				\
			(struct bst_link**)pproot			\
		)

#define __bstlink_rotate_right(link, pproot)				\
		bstlink_rotate_right					\
		(							\
			(struct bst_link*)link,				\
			(struct bst_link**)pproot			\
		)

#define __bstlink_first(link, type)					\
		(type*)							\
		bstlink_first						\
		(							\
			(const struct bst_link*)(link)			\
		)

#define __bstlink_last(link, type)					\
		(type*)							\
		bstlink_last						\
		(							\
			(const struct bst_link*)(link)			\
		)

#define __bstlink_next(link, type)					\
		(type*)							\
		bstlink_next						\
		(							\
			(const struct bst_link*)(link)			\
		)

#define __bstlink_prev(link, type)					\
		(type*)							\
		bstlink_prev						\
		(							\
			(const struct bst_link*)(link)			\
		)

#define __bstlink_init(link, parent, plink)				\
		bstlink_init						\
		(							\
			(struct bst_link*)(link),			\
			(struct bst_link*)(parent),			\
			(struct bst_link**)(plink)			\
		)

__END_DECLS

#endif	/* __YCALGOS_BSTREE_LINK_H_ */
