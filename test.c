#include "stdlib.h"
#include "stdio.h"
#include "common_define.h"
#include "list.h"
#include "stack.h"
#include "stack_limit.h"

static enum StdRet test_entry_list(void)
{
	int *tmp;
	struct list_head *lp;
	lp = (struct list_head *)malloc(sizeof(struct list_head));
	RETURN_ON_NULL(lp);

	INIT_LIST_HEAD(lp);

	struct list_head *nod_0,*nod_1;
	int databuf[3] = {2,4,8};

	nod_0 = (struct list_head *)malloc(sizeof(struct list_head));
	RETURN_ON_NULL(nod_0);
	nod_1 = (struct list_head *)malloc(sizeof(struct list_head));
	RETURN_ON_NULL(nod_1);

	nod_0->data = databuf;
	nod_1->data = databuf + 1;

	list_add_tail(nod_0,lp);
	list_add_tail(nod_1,lp);

	struct list_head *pos;
	list_for_each_entry(pos,lp)
	{
		//printf("%d \n",(*(pos->data)));
		tmp = (pos->data);
		if(*tmp == databuf[1])
			list_del(pos);
		printf("%d\n",*tmp);
	}
	list_for_each_entry(pos,lp)
	{
		tmp = (pos->data);
		printf("%d\n\n",*tmp);
	}
	list_add(nod_1,lp);
	list_for_each_entry(pos,lp)
	{
		tmp = (pos->data);
		printf("%d\n",*tmp);
	}

	return OK;
}

static enum StdRet test_entry_stack(void)
{
	int *tmp;
	struct list_head *stk;
	stk = (struct list_head *)malloc(sizeof(struct list_head));
	RETURN_ON_NULL(stk);

	INIT_STACK(stk);

	struct list_head *nod_0,*nod_1;
	int databuf[3] = {2,4,8};

	nod_0 = (struct list_head *)malloc(sizeof(struct list_head));
	RETURN_ON_NULL(nod_0);
	nod_1 = (struct list_head *)malloc(sizeof(struct list_head));
	RETURN_ON_NULL(nod_1);

	nod_0->data = databuf;
	nod_1->data = databuf + 1;

	stack_push(nod_0,stk);
	stack_push(nod_1,stk);

	struct list_head *pos;
	list_for_each_entry(pos,stk)
	{
		tmp = (pos->data);
		printf("%d\n",*tmp);
	}
	printf("len %d\n", stack_get_len(stk));

	pos = stack_pop(stk);
	printf("pop res %d\n", *((int *)(pos->data)));

	list_for_each_entry(pos,stk)
	{
		tmp = (pos->data);
		printf("%d\n",*tmp);
	}

	printf("len %d\n\n", stack_get_len(stk));

	stack_clear(stk);
	list_for_each_entry(pos,stk)
	{
		tmp = (pos->data);
		printf("%d\n",*tmp);
	}

	return OK;
}

static enum StdRet test_entry_stack_limit(void)
{
	int databuf[4] = {2,4,8,12};
	void *data;
	struct list_head *node;
	struct stack_limit *stack = (struct stack_limit*)malloc(sizeof(struct stack_limit));
	RETURN_ON_NULL(stack);

	stack->stack_size = 4;
	stack_limit_init(stack);

	if(stack_limit_push(stack,databuf,STACK_DIR_LEFT) != OK)
	{
		printf("Push to Left Fail!\n");
		return NG;
	}
	if(stack_limit_push(stack,databuf+1,STACK_DIR_LEFT) != OK)
	{
		printf("Push to Right Fail!\n");
		return NG;
	}

	printf("travel L begin\n");
	lstack_limit_for_each_entry(node,stack)
	{
		if(!node->data)
		{
			continue;
		}
		printf("%d\n", *((int *)(node->data)));
	}
	printf("travel L end\n");

	if(stack_limit_pop(stack,&data,STACK_DIR_LEFT) != OK)
	{
		printf("Pop From Left Fail!\n");
		return NG;
	}
	else
		printf("pop left %d\n", *((int *)(data)));

	return OK;
}

int main()
{
	if(test_entry_list() != OK)
	{
		printf("Error!\n");
	}
	else
		printf("List Test Pass!\n");

	if(test_entry_stack() != OK)
	{
		printf("Error!\n");
	}
	else
		printf("Stack Test Pass!\n");

	if(test_entry_stack_limit() != OK)
	{
		printf("Error\n");
	}
	else
		printf("Stack Limit Test Pass!\n");
	return 0;
}
