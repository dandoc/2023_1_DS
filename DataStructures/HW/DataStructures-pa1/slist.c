#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

slist * slist_alloc (size_t elem_size, int (* compare)(void * e1, void * e2)) 
{
	slist *l = (slist *)malloc(sizeof(slist));
	l->head.elem = 0x0;
	l->head.next = &l->tail;
	l->head.prev = 0x0;
	
	l->tail.elem = 0x0;
	l->tail.next = 0x0;
	l->tail.prev = &l->head;

	l->elem_size = elem_size;
	l->elem_compare = compare;

	return l;
}

void slist_free (slist * l)
{
	if(l == 0x0)
	{
		free(l);
		return;
	}
	slist_node *cur = &l->head;
	while(cur == 0x0)
	{
		slist_node *tmp = cur->next;
		free(cur->elem);
		free(cur);
		cur = cur->next;
	}
	free(l);
}

int slist_length (slist * l)
{
	if(l == 0x0)
		return 0;
	slist_node * i = l->head.next;
	int length = 0;
	for(; i != &l->tail; i = i->next)
		length++;
	return length;
}



int slist_search (slist * l, int (* elem_cond)(void * e))
{
	if(l == 0x0)
		return -1;
	slist_node *cur = l->head.next;
	int index = 0;
	for (; cur != &l->tail ; cur = cur->next)
	{
		if(elem_cond(cur->elem))
		{
			return index;
		}
		index++;
	}
	return -1;
}

int slist_add (slist * l, void * e)
{
	if(l == 0x0 || e == 0x0)
		return 0;
	slist_node *n, *cur = &l->head;
	n = (slist_node * )malloc(sizeof(slist_node));
	n->elem = malloc(l->elem_size);
	memcpy(n->elem, e, l->elem_size);

	while(cur->next != &l->tail && (l->elem_compare(n->elem, cur->next->elem) == -1))
	{
		cur = cur->next;
	}

	n->next = cur->next;
	n->prev = cur;
	cur->next->prev = n;
	cur->next = n;

	return 1 ;
}

int slist_remove (slist * l, int i, void * e)
{
	if(l == 0x0 || i < 0)
		return 0;
	slist_node *cur = l->head.next;
	for(int j = 0; j < i; j++)
	{	
		if(cur == &l->tail)
			return 0;
		cur = cur->next;
	}
	cur->next->prev = cur->prev;
	cur->prev->next = cur->next;
	memcpy(e, cur->elem, l->elem_size);
	free(cur->elem);
	free(cur);
	return 1;
}

void slist_print (slist * l, void (* elem_print)(void * e))
{
	if(l == 0x0 || slist_length(l) == 0)
		return;
	slist_node *cur = l->head.next;
	for (; cur != &l->tail ; cur = cur->next)
	{
		elem_print(cur->elem);
	}
	printf("\n");
}

slist * slist_merge(slist * l1, slist * l2)
{
	if(l1 == 0x0 || l2 == 0x0 || (slist_length(l1) != slist_length(l2)))
		return 0x0;

	slist *l3 = slist_alloc(l1->elem_size, l1->elem_compare);
	
	slist_node *cur3 = &l3->head;
	slist_node *cur1 = l1->head.next;
	slist_node *cur2 = l2->head.next;

	while (cur1 != &l1->tail && cur2 != &l2->tail)
	{
		if(l3->elem_compare(cur1->elem, cur2->elem) >= 0)
		{
			slist_node *tmp = (slist_node *)malloc(sizeof(slist_node));
			memcpy(tmp, cur1, sizeof(cur1));

			tmp->next = cur3->next;
			tmp->prev = cur3;

			cur3->next->prev = tmp;
			cur3->next = tmp;

			cur1 = cur1->next;
			cur3 = cur3->next;
		}

		else if(l3->elem_compare(cur1->elem, cur2->elem) < 0)
		{
			slist_node *tmp = (slist_node *)malloc(sizeof(slist_node));

			memcpy(tmp, cur2, sizeof(cur2));
			
			tmp->next = cur3->next;
			tmp->prev = cur3;

			cur3->next->prev = tmp;
			cur3->next = tmp;

			cur2 = cur2->next;
			cur3 = cur3->next;
		}
	}

	if(cur1 == &l1->tail)
	{
			slist_node *tmp = (slist_node *)malloc(sizeof(slist_node));
			memcpy(tmp, cur2, sizeof(cur2));
			tmp->next = cur3->next;
			tmp->prev = cur3;
			cur3->next->prev = tmp;
			cur3->next = tmp;

			cur2 = cur2->next;
			cur3 = cur3->next;
			return l3;
	}

	else if(cur2 == &l2->tail)
	{
			slist_node *tmp = (slist_node *)malloc(sizeof(slist_node));
			memcpy(tmp, cur1, sizeof(cur1));
			tmp->next = cur3->next;
			tmp->prev = cur3;
			cur3->next->prev = tmp;
			cur3->next = tmp;

			cur1 = cur1->next;
			cur3 = cur3->next;
			return l3;
	}

}

