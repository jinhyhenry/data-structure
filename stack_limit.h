#ifndef _STACK_LIMIT_H_
#define _STACK_LIMIT_H_

#include "list.h"
#include "stack.h"
#include "common_define.h"

struct stack_limit {
	struct list_head *head,*lhead,*rhead;
	int stack_size;
};

enum STACK_DIR {
	STACK_DIR_LEFT,
	STACK_DIR_RIGHT,
};

static void stack_limit_init(struct stack_limit *stack)
{
	int i,num,len;
	num = stack->stack_size;

	struct list_head *node;
	stack->head = (struct list_head *)malloc(sizeof(struct list_head));

	INIT_LIST_HEAD(stack->head);

	for(i=0;i<num;i++)
	{
		node = (struct list_head *)malloc(sizeof(struct list_head));
		list_add_tail(node,stack->head);
	}

	stack->lhead = stack->head;
	stack->rhead = stack->head;
}

static inline BOOL stack_limit_full(struct stack_limit *stack)
{
	if(stack->lhead->next == stack->rhead)
		return TRUE;
	else
		return FALSE;
}

static inline BOOL stack_limit_empty(struct stack_limit *stack,enum STACK_DIR stack_dir)
{
	if(stack_dir == STACK_DIR_LEFT)
	{
		if(stack->lhead == stack->head)
		{
			return TRUE;
		}
		else
			return FALSE;
	}
	if(stack_dir == STACK_DIR_RIGHT)
	{
		if(stack->rhead == stack->head)
		{
			return TRUE;
		}
		else
			return FALSE;
	}
	return FALSE;
}

static inline enum StdRet stack_limit_push(struct stack_limit *stack,void *data,enum STACK_DIR stack_dir)
{
	if(stack_limit_full(stack))
		return OVER_FLOW;
	if(stack_dir == STACK_DIR_LEFT)
	{
		stack->lhead = stack->lhead->next;
		stack->lhead->data = data;
	}
	else
	{
		stack->rhead = stack->rhead->prev;
		stack->rhead->data = data;
	}
	return OK;
}

static inline enum StdRet stack_limit_pop(struct stack_limit *stack,void **data,enum STACK_DIR stack_dir)
{
	if(stack_limit_empty(stack,stack_dir) == TRUE)
	{
		return NULL_PTR;
	}

	if(stack_dir == STACK_DIR_LEFT)
	{
		*data = stack->lhead->data;
		stack->lhead = stack->lhead->prev;
	}
	else
	{
		*data = stack->rhead->data;
		stack->rhead = stack->rhead->next;
	}
	return OK;
}

#define lstack_limit_for_each_entry(pos, stack) \
    for(pos = stack->lhead;pos != stack->head;pos = pos->prev)

#define rstack_limit_for_each_entry(pos, stack) \
    for(pos = stack->rhead;pos != stack->head;pos = pos->next)

#endif