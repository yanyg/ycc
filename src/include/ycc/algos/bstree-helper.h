/*
 * bstree-helper.h -- Binary-Search-Trees Common Routines
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

#include <ycc/algos/bstree-link.h>
#include <ycc/algos/rbtree.h>
#include <ycc/algos/avltree.h>

typedef void (*__bst_destroy_t)(struct bst_link *link, const void *arg);
typedef int (*__bst_compare_t)(const struct bst_link *link, const void *arg);
typedef int (*__bst_compare_link_t)(const struct bst_link *link1,
				    const struct bst_link *link2,
				    const void *arg);
typedef void (*__bst_visit_t)(const struct bst_link *link, const void *arg);
typedef bool (*__bst_visit_cond_t)(const struct bst_link *link,
				   const void *arg);

/*
 * __bst_find  --  find the left-most node
 *
 * Description
 *	The function finds the left-most node of the 'link' subtree,
 *	the node's value is equals to 'arg' which judged by routine
 *	'compare'
 *
 * Parameters
 *	link	: the root node of search-tree
 *	compare	: pointer of value compares routine
 *	arg	: transfer to 'compare' transparently
 *
 * Return value
 *	The left-most node which value is equals to 'arg' or
 *	NULL if no-match found.
 */
struct bst_link *__bst_find(const struct bst_link *link,
			    __bst_compare_t compare,
			    const void *arg);

/*
 * __bst_lower_bound
 *
 * Description
 *	The function finds the first node of the 'link' subtree,
 *	the node's value is equals to or greater than 'arg' which
 *	judged by routine 'compare'
 *
 * Parameters
 *	link	: the root node of search-tree
 *	compare	: pointer of value compares routine
 *	arg	: transfer to 'compare' transparently
 *
 * Return value
 *	The first node which value is equals to or greater than 'arg' or
 *	NULL if no-match found.
 */
struct bst_link *__bst_lower_bound(const struct bst_link *link,
				   __bst_compare_t compare,
				   const void *arg);

/*
 * __bst_upper_bound
 *
 * Description
 *	The function finds the first node of the 'link' subtree,
 *	the node's value is greater than 'arg' which judged by
 *	routine 'compare'
 *
 * Parameters
 *	link	: the root node of search-tree
 *	compare	: pointer of value compares routine
 *	arg	: transfer to 'compare' transparently
 *
 * Return value
 *	The first node which value is greater than 'arg' or
 *	NULL if no-match found.
 */
struct bst_link *__bst_upper_bound(const struct bst_link *link,
				   __bst_compare_t compare,
				   const void *arg);

/*
 * __bst_lower_upper_bound -- the merge of two routines above
 */
void __bst_lower_upper_bound(const struct bst_link *link,
			     __bst_compare_t compare,
			     const void *arg,
			     struct bst_link **plower,
			     struct bst_link **pupper);

/*
 * __bst_count  --  count of nodes which value equal to
 */
size_t __bst_count(const struct bst_link *link,
		   __bst_compare_t compare,
		   const void *arg);

/* destroy all link and its descendant */
void __bst_destroy(struct bst_link *link,
		   bstlink_destroy_t destroy,
		   const void *arg);

/* inorder-traverse */
void __bst_visit(struct bst_link *link,
		 bstlink_visit_t visit,
		 const void *arg);
bool __bst_visit_cond(struct bst_link *link,
		      bstlink_visit_cond_t visit_cond,
		      const void *arg);

static inline size_t __bst_depth(const struct bst_link *link, bool bmax)
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

#define __bstlink_destroy(link, destroy, arg)	bstlink_destroy(	\
		(struct bst_link*)(link),				\
		(bstlink_destroy_t)(destroy),				\
		(const void*)(arg))
/* eof */
