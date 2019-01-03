#ifndef _STACK_H_
#define _STACK_H_

#include "list.h"

static inline void INIT_STACK(struct list_head *stack)
{
	INIT_LIST_HEAD(stack);
	stack->data = (int *)malloc(sizeof(int));
	*((int *)(stack->data)) = 0;
}

static inline void stack_push(struct list_head *new, struct list_head *head)
{
	list_add(new, head);
	*((int *)(head->data)) += 1;
}

static inline struct list_head *stack_pop(struct list_head *head)
{
	struct list_head *nod;
	nod = head->next;
	list_del(nod);
	*((int *)(head->data)) -= 1;
	return nod;
}

static inline struct list_head *stack_get_top(struct list_head *head)
{
	return head->next;
}

static inline int stack_get_len(struct list_head *stack)
{
	return *((int *)(stack->data));	
}

static inline void stack_clear(struct list_head *stack)
{
	struct list_head *tmp;
	while(!list_empty(stack))
		stack_pop(stack);
}

#endif