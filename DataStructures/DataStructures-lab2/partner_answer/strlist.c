#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strlist.h"

strlist * strlist_alloc () 
{
	strlist * l ;
	l = (strlist *) malloc(sizeof(strlist)) ;
	l->head = 0x0 ;
	return l ;
}

void strlist_free (strlist * l) 
{
	while (l->head != 0x0) {
		char * s ;
		strlist_remove_first(l, &s) ;
	}	
}

int strlist_add_first (strlist * l, char * s)
{
	strlist_node * n ;
	n = (strlist_node *) malloc(sizeof(strlist_node)) ;
	n->elem = s ;
	n->next = l->head ;
	l->head = n ;
	return 1 ;
}

int strlist_add_last (strlist * l, char * s) 
{
	/* TODO */
	strlist_node * i = l->head;
	for (i = l->head ; i != 0x0 ; i = i->next) {
		if(i->next == 0x0)
		{
			strlist_node * n ;
			n = (strlist_node *) malloc(sizeof(strlist_node)) ;
			if(n == 0x0)
				return 0;
			n->elem = s ;
			i->next = n ;
			return 1;
		}
	}
	return 0;
}

int strlist_search (strlist * l, char * s, int i) 
{
	strlist_node * cur;
	int n = 0;
	int appear = 0;
	for (cur = l->head ; cur != 0x0 ; cur = cur->next)
	{
		if(strcmp(s, cur->elem)==0)
		{
			
			if(i == appear){
				return n+1;
			}
			appear++;
		}
		n++;
	}
	return 0;


	printf("\n") ;
}

int strlist_remove (strlist * l, int i, char ** s)
{
	/* TODO */
	strlist_node * cur;
	strlist_node * prev;
	int n = 0;
	for (cur = l->head ; cur != 0x0 ; cur = cur->next) {
		if(n==i-1)
		{
			*s = cur->elem;

			prev->next = cur->next;
			free(cur);
			return 1;
		}
		prev = cur;
		n++;
	}
	return 0;

}


int strlist_remove_first (strlist * l, char ** s) 
{
	if (l->head == 0x0)
		return 0 ;

	strlist_node * n ;
	n = l->head ;
	l->head = n->next ;
	*s = n->elem ;
	free(n) ;
	return 1 ;
}

void strlist_print (strlist * l) 
{
	strlist_node * i ;
	for (i = l->head ; i != 0x0 ; i = i->next) {
		printf("\"%s\" ", i->elem) ;
	}
	printf("\n") ;
}
