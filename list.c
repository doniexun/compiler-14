#include <stdlib.h>
#include "list.h"
#include "error.h"

struct list* new_list(void* data)
{
	struct list*	list;

	list = malloc(sizeof(struct list));	
	
	if (NULL == list)
		error("Out of memory\n");
	
	list->data = data;
	list->succ = list;
	list->pred = list;

	return list;
}

void free_node(struct list* list)
{
	list->succ->pred = list->pred;	
	list->pred->succ = list->succ;
	free(list);
}


void* remove_first(struct list** list)
{
	struct list* 	next;
	void*		data;

	data = (*list)->data;
	next = (*list)->succ;

	if (*list == NULL)
		return NULL;

	else if (*list == next) {
		free_node(list);
		*list = NULL;
	} else {
		free_node(list);
		*list = next;	
	}

	return data;
}

void add_last(struct list* list, void* data)
{
	struct list*	p;

	p = new_list(data);

	p->succ = list;
	p->pred = list->pred;

	list->pred->succ = p;
	list->pred = p;
}

void free_list(struct list** list)
{
	struct list* p;
	struct list* h;
	struct lisT* q;

	p = h = *list;

	if (NULL == p)
		return;

	while (p->succ != h) {
		q = p;
		p = p->succ;
		free_node(q);
	}

	free_node(h);

	*list = NULL;
}
