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
 * You alawys need not to include this file directly.
 * This file is designed to provide basic binary search tree routines,
 * And the interface is volatile 
 */

#ifndef __YCALGOS_BSTREE_LINK_H_
#define __YCALGOS_BSTREE_LINK_H_

#include <stddef.h>
#include <stdbool.h>

#include <ycc/compiler.h>

__BEGIN_DECLS

/* bstlink: Binary Search Tree Link  */
#define bst_link_member(type)	\
	type *parent, *left, *right
struct bst_link
{
	bst_link_member(struct bst_link);
}__aligned(sizeof(void*));

typedef void (*bstlink_destroy_t)(struct bst_link *link, const void *arg);
typedef int (*bstlink_compare_t)(const struct bst_link *link, const void *arg);
typedef void (*bstlink_visit_t)(const struct bst_link *link, const void *arg);
typedef bool
(*bstlink_visit_cond_t)(const struct bst_link *link, const void *arg);

void bstlink_rotate_left(struct bst_link *link, struct bst_link **pproot);
void bstlink_rotate_right(struct bst_link *link, struct bst_link **proot);
struct bst_link *bstlink_first(const struct bst_link *link);
struct bst_link *bstlink_last(const struct bst_link *link);
struct bst_link *bstlink_next(const struct bst_link *link);
struct bst_link *bstlink_prev(const struct bst_link *link);
struct bst_link *bstlink_find(const struct bst_link *link,
			      bstlink_compare_t cond,
			      const void *arg);
/* first equal or greater node */
struct bst_link *bstlink_lower_bound(const struct bst_link *link,
				     bstlink_compare_t compare,
				     const void *arg);
/* first greater node */
struct bst_link *bstlink_upper_bound(const struct bst_link *link,
				     bstlink_compare_t compare,
				     const void *arg);
void bstlink_lower_upper_bound(const struct bst_link *link,
			       bstlink_compare_t compare,
			       const void *arg,
			       struct bst_link **plower,
			       struct bst_link **pupper);
size_t bstlink_count(const struct bst_link *link,
				     bstlink_compare_t compare,
				     const void *arg);
/* destroy all link and its descendant */
void bstlink_destroy(struct bst_link *link,
		     bstlink_destroy_t destroy,
		     const void *arg);

/* inorder-traverse */
void bstlink_visit(struct bst_link *link,
		   bstlink_visit_t visit,
		   const void *arg);
bool bstlink_visit_cond(struct bst_link *link,
		   bstlink_visit_cond_t visit_cond,
		   const void *arg);

static inline void bstlink_init(struct bst_link *link,
				struct bst_link *parent,
				struct bst_link **plink)
{
	link->parent = parent;
	link->left = link->right = NULL;
	*plink = link;
}

static inline size_t bstlink_depth(const struct bst_link *link, bool bmax)
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

/*
 * Type auto-convert macros
 * Be careful! The below macros are dangerous !!!
 */
#define __bstlink_depth_max(link)			\
		bstlink_depth				\
		(					\
			(const struct bst_link*)(link),	\
			true				\
		)

#define __bstlink_depth_min(link)			\
		bstlink_depth				\
		(					\
			(const struct bst_link*)(link),	\
			false				\
		)

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

#define __bstlink_find(link, compare, arg, type)			\
		(type*)							\
		bstlink_find						\
		(							\
			(const struct bst_link*)(link),			\
			(bstlink_compare_t)(compare),			\
			(const void*)(arg)				\
		)

#define __bstlink_lower_bound(link, compare, arg, type)			\
		(type*)							\
		bstlink_lower_bound					\
		(							\
			(struct bst_link*)(link),			\
			(bstlink_compare_t)(compare),			\
			(const void*)(arg)				\
		)

#define __bstlink_upper_bound(link, compare, arg, type)			\
		(type*)							\
		bstlink_upper_bound					\
		(							\
			(struct bst_link*)(link),			\
			(bstlink_compare_t)(compare),			\
			(const void*)(arg)				\
		)

#define __bstlink_lower_upper_bound(link, compare, arg, plower, pupper)	\
		bstlink_lower_upper_bound				\
		(							\
			(const struct bst_link*)(link),			\
			(bstlink_compare_t)(compare),			\
			(const void*)(arg),				\
			(struct bst_link**)(plower),			\
			(struct bst_link**)(pupper)			\
		)

#define __bstlink_init(link, parent, plink)				\
		bstlink_init						\
		(							\
			(struct bst_link*)(link),			\
			(struct bst_link*)(parent),			\
			(struct bst_link**)(plink)			\
		)

#define __bstlink_destroy(link, destroy, arg)	bstlink_destroy(	\
		(struct bst_link*)(link),				\
		(bstlink_destroy_t)(destroy),				\
		(const void*)(arg))

__END_DECLS

#endif	/* __YCALGOS_BSTREE_LINK_H_ */
