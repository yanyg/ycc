/*
 * avltree.h -- Self-balancing Binary Search Trees
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
 * To use avltrees you'll have to implement your own insert and search cores.
 * This will avoid us to use callbacks and to drop drammatically performances.
 *
 * Example of insert and search as follows
 */

#if 0
Example of insert and search routines.
#endif

#ifndef __YC_ALGOS_AVLTREE_H_
#define __YC_ALGOS_AVLTREE_H_

#include <ycc/algos/bstree-link.h>

__BEGIN_DECLS

struct avl_node
{
	bst_link_member(struct avl_node);
	unsigned depth;
} __aligned(sizeof(void*));

struct avl_root
{
	struct avl_node *node;
};

#define avl_entry(ptr, type, member)	container_of(ptr, type, member)

#define AVL_DECLARE(name)	struct avl_root name =  { NULL, }
#define AVL_INIT(name)	do { (name).node = NULL; } while (0)
static inline void avl_init(struct avl_root *avl)
{
	AVL_INIT(*avl);
}

static inline void avl_link_node(struct avl_node *node,
				struct avl_node *parent,
				struct avl_node **pnode)
{
	__bstlink_init(node, parent, pnode);
	node->depth = 1;
}

static inline struct avl_node *avl_first(const struct avl_root *avl)
{
	return __bstlink_first(avl->node, struct avl_node);
}

static inline struct avl_node *avl_last(const struct avl_root *avl)
{
	return __bstlink_last(avl->node, struct avl_node);
}

static inline struct avl_node *avl_next(const struct avl_node* node)
{
	return __bstlink_next(node, struct avl_node);
}

static inline struct avl_node *avl_prev(const struct avl_node* node)
{
	return __bstlink_prev(node, struct avl_node);
}

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

__END_DECLS

#endif /* __YC_ALGOS_avlTREE_H_ */
