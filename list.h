#ifndef _LIST_H_
#define _LIST_H_

struct list_head {
	struct list_head *next, *prev;
	void *data;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	//entry->next = NULL;
	//entry->prev = NULL;
}

/*1 -- empty; 0 -- not*/
static inline int list_empty(struct list_head *head)
{
	if(head->next == head){
		return 1;
	}
	else
		return 0;
}

#define list_for_each_entry(pos, head) \
    for(pos = head->next;pos != head;pos = pos->next)
#endif

