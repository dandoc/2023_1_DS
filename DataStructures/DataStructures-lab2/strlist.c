#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strlist.h"

strlist *strlist_alloc()
{
	strlist *l;
	l = (strlist *)malloc(sizeof(strlist));
	l->head = 0x0;
	return l;
}

void strlist_free(strlist *l)
{
	while (l->head != 0x0)
	{
		char *s;
		strlist_remove_first(l, &s);
	}
}

int strlist_add_first(strlist *l, char *s)
{
	strlist_node *n;
	n = (strlist_node *)malloc(sizeof(strlist_node));
	n->elem = s;
	n->next = l->head;
	l->head = n;
	return 1;
}

int strlist_add_last(strlist *l, char *s)
{
	if(l->head == 0x0)	return strlist_add_first(l, s);
	strlist_node *i = l->head;
	for (; i != 0x0; i = i->next)
	{
		if (i->next == 0x0)
		{
			strlist_node *n;
			n = (strlist_node *)malloc(sizeof(strlist_node));
			n->elem = s;
			i->next = n;
			return 1;
		}
	}
	return 0;
}

int strlist_search(strlist *l, char *s, int i)
{
	strlist_node *j = l->head;
	int n = 0, c = 0;
	for (; j != 0x0; j = j->next)
	{
		if (!strcmp(s, j->elem))
		{
			if (c == i)
				return n + 1;
			c++;
		}
		n++;
	}
	return -1;
}

int strlist_remove(strlist *l, int i, char **s)
{
	if(l->head == 0x0)	return 0;
	if(i==0) return(strlist_remove_first(l, s));
	int j = 0;
	strlist_node *cur = l->head;
	strlist_node *prev = 0x0;
	for(; cur != 0x0; cur = cur->next)
	{
		if(j==i)
		{
			*s = cur->elem;
			prev->next = cur->next;
			free(cur);
			return 1;
		}
		prev = cur;
		j++;
	}
	free(cur);
	return 0;
}

int strlist_remove_first(strlist *l, char **s)
{
	if (l->head == 0x0)
		return 0;

	strlist_node *n;
	n = l->head;
	l->head = n->next;
	*s = n->elem;
	free(n);
	return 1;
}

void strlist_print(strlist *l)
{
	strlist_node *i;
	for (i = l->head; i != 0x0; i = i->next)
	{
		printf("\"%s\" ", i->elem);
	}
	printf("\n");
}
