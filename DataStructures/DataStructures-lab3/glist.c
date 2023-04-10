#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glist.h"

glist *glist_alloc(size_t s)
{
	glist *l = (glist *)malloc(sizeof(glist));
	l->head = 0x0;
	l->size = s;
	return l;
}

void glist_free(glist *l)
{
	while (l->head != 0x0)
	{
		glist_remove_first(l, 0x0);
	}
}

int glist_search (glist * l, int (* elem_cond)(void *s))
{	
	int idx = 0;
	glist_node * i;
	for(i = l->head; i != 0x0; i = i->next){
		if(1 == elem_cond(i->elem)){
			return idx;
		}
		idx ++;
	}
	return -1;

}

int glist_add_first(glist *l, void *s)
{
	glist_node *n = (glist_node *)malloc(sizeof(glist_node));
	n->elem = malloc(l->size);
	memcpy(n->elem, s, l->size);
	n->next = l->head;
	l->head = n;
}

int glist_add_last(glist *l, void *s)
{
	glist_node *i;
	glist_node *n;
	n = (glist_node *)malloc(sizeof(glist_node));
	n->elem = malloc(l->size);
	memcpy(n->elem, s, l->size);
	for (i = l->head; i != 0x0; i = i->next){
		if(i->next == 0x0){
			i->next = n;
			return 1;
		}
	}
	return 0;
}

int glist_remove(glist *l, int i, void *s)
{	
	glist_node * n;
	glist_node * tmp;
	int idx = 0;
	if(l->head == 0x0){
		return 1;
	}
	if(i==0){
		return glist_remove_first(l, s);
	}
	for(n = l->head; n != 0x0; n = n->next){
		if(idx==i-1){
			tmp = n;
		}
		if(idx == i){
			tmp->next = n->next;
			//s 가 null인지 체크
			memcpy(s, n->elem, l->size);
			free(n->elem);
			free(n);
			return 1;
		}
		idx++;
	}
	return 0;
}

int glist_remove_first(glist *l, void *s)
{
	if (l->head == 0x0)
		return 0;

	glist_node *n = l->head;
	l->head = n->next;
	if (s != 0x0)
	{
		memcpy(s, n->elem, l->size);
	}
	free(n->elem);
	free(n);
	return 1;
}

void glist_print(glist *l, void (*elem_print)(void *))
{
	glist_node *i;
	for (i = l->head; i != 0x0; i = i->next)
	{
		elem_print(i->elem);
		printf(" ");
	}
	printf("\n");
}
