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
	__BST_LINK_MEMBER(struct avl_node);
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
__END_DECLS

#endif /* __YC_ALGOS_avlTREE_H_ */
