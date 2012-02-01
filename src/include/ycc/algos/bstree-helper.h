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
 * __bst_insert_prepare  --  set the link of the node for insert
 */
bool __bst_insert_prepare(struct bst_link *node,
			  struct bst_link **proot,
			  int (*compare_link)(const struct bst_link *link1,
					      const struct bst_link *link2,
					      const void *arg),
			  const void *arg,
			  bool bunique);
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
			     struct bst_link **plb,
			     struct bst_link **pub);

/*
 * __bst_count  --  count of nodes which value equal to
 */
size_t __bst_count(const struct bst_link *link,
		   __bst_compare_t compare,
		   const void *arg);

/* destroy all link and its descendant */
void __bst_destroy(struct bst_link *link,
		   __bst_destroy_t destroy,
		   const void *arg);

/* inorder-traverse */
void __bst_visit(struct bst_link *link,
		 __bst_visit_t visit,
		 const void *arg);
bool __bst_visit_cond(struct bst_link *link,
		      __bst_visit_cond_t visit_cond,
		      const void *arg);

size_t __bst_depth(const struct bst_link *link, bool bmax);

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
			(__bst_compare_t)(compare),			\
			(const void*)(arg)				\
		)

#define __bstlink_lower_bound(link, compare, arg, type)			\
		(type*)							\
		bstlink_lower_bound					\
		(							\
			(struct bst_link*)(link),			\
			(__bst_compare_t)(compare),			\
			(const void*)(arg)				\
		)

#define __bstlink_upper_bound(link, compare, arg, type)			\
		(type*)							\
		bstlink_upper_bound					\
		(							\
			(struct bst_link*)(link),			\
			(__bst_compare_t)(compare),			\
			(const void*)(arg)				\
		)

#define __bstlink_lower_upper_bound(link, compare, arg, plower, pupper)	\
		bstlink_lower_upper_bound				\
		(							\
			(const struct bst_link*)(link),			\
			(__bst_compare_t)(compare),			\
			(const void*)(arg),				\
			(struct bst_link**)(plower),			\
			(struct bst_link**)(pupper)			\
		)

#define __bstlink_destroy(link, destroy, arg)	bstlink_destroy(	\
		(struct bst_link*)(link),				\
		(__bst_destroy_t)(destroy),				\
		(const void*)(arg))

/* rbtree */
static inline struct rb_node *
rb_find(const struct rb_root *rb,
	int (*compare)(const struct rb_node *node,
		       const void *arg),
		       const void *arg)
{
	return __bstlink_find(rb->node, compare, arg, struct rb_node);
}

static inline struct rb_node *rb_lower_bound(struct rb_root *rb,
					     int (*compare)(
						  const struct rb_node *node,
						  const void *arg),
					     const void *arg)
{
	return __bstlink_lower_bound(rb->node, compare, arg, struct rb_node);
}

static inline struct rb_node *rb_upper_bound(struct rb_root *rb,
					     int (*compare)(
						  const struct rb_node *node,
						  const void *arg),
					     const void *arg)
{
	return __bstlink_upper_bound(rb->node, compare, arg, struct rb_node);
}

static inline void
rb_lower_upper_bound(struct rb_root *rb,
		     int (*compare)(const struct rb_node *node,
		     const void *arg),
		     const void *arg,
		     struct rb_node **plower,
		     struct rb_node **pupper)
{
	__bstlink_lower_upper_bound(rb->node, compare, arg, plower, pupper);
}

void rb_insert(struct rb_node *node,
	       struct rb_root *rb,
	       int (*compare_link)(const struct rb_node *node1,
				   const struct rb_node *node2,
				   const void *arg),
	       const void *arg);
bool rb_insert_unique(struct rb_node *node,
	       struct rb_root *rb,
	       int (*compare_link)(const struct rb_node *node1,
				   const struct rb_node *node2,
				   const void *arg),
	       const void *arg);

void rb_erase_equal(struct rb_root *rb,
		    int (*compare)(const struct rb_node *node,
				   const void *arg),
		    void (*destroy)(struct rb_node *node, const void *arg),
		    const void *arg_compare,
		    const void *arg_destroy);

static inline void rb_clear(struct rb_root *rb,
			    void (*destroy)(struct rb_node *node,
					    const void *arg),
			    const void *arg)
{
	__bstlink_destroy(rb->node, destroy, arg);
	rb_init(rb);	/* re-init */
}

static inline size_t rb_depth_max(const struct rb_root *rb)
{
	return __bstlink_depth_max(rb->node);
}

static inline size_t rb_depth_min(const struct rb_root *rb)
{
	return __bstlink_depth_min(rb->node);
}

/* avltree */
static inline struct avl_node *
avl_find(const struct avl_root *avl,
	int (*compare)(const struct avl_node *node,
		       const void *arg),
		       const void *arg)
{
	return __bstlink_find(avl->node, compare, arg, struct avl_node);
}

static inline struct avl_node *avl_lower_bound(struct avl_root *avl,
					     int (*compare)(
						  const struct avl_node *node,
						  const void *arg),
					     const void *arg)
{
	return __bstlink_lower_bound(avl->node, compare, arg, struct avl_node);
}

static inline struct avl_node *avl_upper_bound(struct avl_root *avl,
					     int (*compare)(
						  const struct avl_node *node,
						  const void *arg),
					     const void *arg)
{
	return __bstlink_upper_bound(avl->node, compare, arg, struct avl_node);
}

static inline void
avl_lower_upper_bound(struct avl_root *avl,
		     int (*compare)(const struct avl_node *node,
		     const void *arg),
		     const void *arg,
		     struct avl_node **plower,
		     struct avl_node **pupper)
{
	__bstlink_lower_upper_bound(avl->node, compare, arg, plower, pupper);
}

void avl_insert(struct avl_node *node,
	       struct avl_root *avl,
	       int (*compare_link)(const struct avl_node *node1,
				   const struct avl_node *node2,
				   const void *arg),
	       const void *arg);
bool avl_insert_unique(struct avl_node *node,
	       struct avl_root *avl,
	       int (*compare_link)(const struct avl_node *node1,
				   const struct avl_node *node2,
				   const void *arg),
	       const void *arg);
void avl_insert_depth(struct avl_node *node, struct avl_root *avl);

void avl_erase(struct avl_node *node, struct avl_root *avl);
void avl_erase_range(struct avl_node *beg,
		    struct avl_node *end,
		    struct avl_root *avl);
void avl_erase_equal(struct avl_root *avl,
		    int (*compare)(const struct avl_node *node,
				   const void *arg),
		    void (*destroy)(struct avl_node *node, const void *arg),
		    const void *arg_compare,
		    const void *arg_destroy);

static inline void avl_clear(struct avl_root *avl,
			    void (*destroy)(struct avl_node *node,
					    const void *arg),
			    const void *arg)
{
	__bstlink_destroy(avl->node, destroy, arg);
	avl_init(avl);	/* re-init */
}

struct avl_root *avl_alloc(size_t num);
void avl_free(struct avl_root *avl,
	     size_t num,
	     void (*destroy)(struct avl_node *avl, const void *arg),
	     const void *arg);

bool avl_clone(struct avl_root *avl,
	      const struct avl_root *avl_src,
	      struct avl_node *(*node_clone)(const struct avl_node *node,
					    const void *arg),
	      void (*node_destroy)(struct avl_node *node, const void *arg),
	      const void *arg_clone,
	      const void *arg_destroy);

/* clone range: [beg, end) */
bool avl_clone_range(struct avl_root *avl,
		    const struct avl_node *beg,
		    const struct avl_node *end,
		    struct avl_node *(*node_clone)(const struct avl_node *node,
						  const void *arg),
		    void (*node_destroy)(struct avl_node *node,
					 const void *arg),
		    const void *arg_clone,
		    const void *arg_destroy);

static inline void avl_swap(struct avl_root *avl1, struct avl_root *avl2)
{
	struct avl_node *node = avl1->node;
	avl1->node = avl2->node;
	avl2->node = node;
}

static inline size_t avl_depth_max(const struct avl_root *avl)
{
	return __bstlink_depth_max(avl->node);
}

static inline size_t avl_depth_min(const struct avl_root *avl)
{
	return __bstlink_depth_min(avl->node);
}

/* eof */
