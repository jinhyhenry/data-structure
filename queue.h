#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "list.h"

#define INIT_QUEUE_HEAD(queue) INIT_LIST_HEAD(queue)

#define QUEUE_EMPTY(queue) list_empty(queue)

#define ENQUEUE(node,queue) list_add_tail(node,queue)

static inline void DEQUEUE(struct list_head *queue,struct list_head **node)
{
	*node = queue->next;
	list_del(*node);
}

static inline void queue_clear(struct list_head *queue)
{
	struct list_head *node;
	list_for_each_entry(node,queue)
	{
		list_del(node);
		free(node);
	}
}

#endif