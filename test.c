#include "stdlib.h"
#include "stdio.h"
#include "return.h"
#include "list.h"
#include "stack.h"

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

int main()
{
	if(test_entry_list() != OK)
	{
		printf("Error!\n");
	}
	printf("List Test Pass!\n");

	if(test_entry_stack() != OK)
	{
		printf("Error!\n");
	}
	printf("Stack Test Pass!\n");

	return 0;
}
