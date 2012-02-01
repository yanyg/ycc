/*
 * rbtree.h -- Red Black Trees
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
 * To use rbtrees you'll have to implement your own insert and search cores.
 * This will avoid us to use callbacks and to drop drammatically performances.
 *
 * Example of insert and search as follows
 */

#if 0
Example of insert and search routines.
#endif

#ifndef __YC_ALGOS_RBTREE_H_
#define __YC_ALGOS_RBTREE_H_

#include <ycc/algos/bstree-link.h>

__BEGIN_DECLS

struct rb_node
{
	__BST_LINK_MEMBER(struct rb_node);
	unsigned color;
#define RB_COLOR_RED 0
#define RB_COLOR_BLACK 1
} __aligned(sizeof(void*));

struct rb_root
{
	struct rb_node *node;
};

#define rb_entry(ptr, type, member)	container_of(ptr, type, member)

#define RB_DECLARE(name)	struct rb_root name =  { NULL, }
#define RB_INIT(name)	do { (name).node = NULL; } while (0)
static inline void rb_init(struct rb_root *rb)
{
	RB_INIT(*rb);
}

static inline void rb_link_node(struct rb_node *node,
				struct rb_node *parent,
				struct rb_node **pnode)
{
	__bstlink_init(node, parent, pnode);
	node->color = RB_COLOR_RED;
}

static inline struct rb_node *rb_first(const struct rb_root *rb)
{
	return __bstlink_first(rb->node, struct rb_node);
}

static inline struct rb_node *rb_last(const struct rb_root *rb)
{
	return __bstlink_last(rb->node, struct rb_node);
}

static inline struct rb_node *rb_next(const struct rb_node* node)
{
	return __bstlink_next(node, struct rb_node);
}

static inline struct rb_node *rb_prev(const struct rb_node* node)
{
	return __bstlink_prev(node, struct rb_node);
}

void rb_insert_color(struct rb_node *node, struct rb_root *rb);

void rb_erase(struct rb_node *node, struct rb_root *rb);
void rb_erase_range(struct rb_node *beg,
		    struct rb_node *end,
		    struct rb_root *rb);
struct rb_root *rb_alloc(size_t num);
void rb_free(struct rb_root *rb,
	     size_t num,
	     void (*destroy)(struct rb_node *rb, const void *arg),
	     const void *arg);

bool rb_clone(struct rb_root *rb,
	      const struct rb_root *rb_src,
	      struct rb_node *(*node_clone)(const struct rb_node *node,
					    const void *arg),
	      void (*node_destroy)(struct rb_node *node, const void *arg),
	      const void *arg_clone,
	      const void *arg_destroy);

/* clone range: [beg, end) */
bool rb_clone_range(struct rb_root *rb,
		    const struct rb_node *beg,
		    const struct rb_node *end,
		    struct rb_node *(*node_clone)(const struct rb_node *node,
						  const void *arg),
		    void (*node_destroy)(struct rb_node *node,
					 const void *arg),
		    const void *arg_clone,
		    const void *arg_destroy);

static inline void rb_swap(struct rb_root *rb1, struct rb_root *rb2)
{
	struct rb_node *node = rb1->node;
	rb1->node = rb2->node;
	rb2->node = node;
}

#define rb_color(r)	((r)->color)
#define rb_is_red(r)	(!rb_color(r))
#define rb_is_black(r)	rb_color(r)
#define rb_set_color(r, val)	do { (r)->color = (val); } while(0)
#define rb_set_red(r)	rb_set_color((r), RB_COLOR_RED)
#define rb_set_black(r)	rb_set_color((r), RB_COLOR_BLACK)

__END_DECLS

#endif /* __YC_ALGOS_RBTREE_H_ */
