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
#if 1
#include <ycc/algos/rbtree.h>
#include <ycc/algos/avltree.h>
#endif

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
