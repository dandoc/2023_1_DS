#include <stdio.h>
#include "strlist.h"

int main ()
{
	strlist * l ;

	l = strlist_alloc() ;

	char *s1 = "Rob", *s2 = "Jack", *s3="Mike", *s4 = "Paul", *s5 = "Tim" ;
	

	strlist_add_first(l, s1) ;
	strlist_add_first(l, s2) ;
	strlist_add_first(l, s3) ;
	strlist_add_first(l, s4) ;
	strlist_add_first(l, s1) ;
	strlist_add_first(l, s5) ;

	strlist_print(l) ;

	//task1
	char *s6 = "Lee";
	printf("\nAdding %s to last\n", s6);
	if(strlist_add_last(l, s6))
	{
		printf("Adding last successful\n");
		strlist_print(l);
 	}
	else
	{
		printf("Failed adding last\n");
		strlist_print(l);
	}

	//task2
	printf("\nSearching first Rob\n");
	int result = strlist_search(l, s1, 0);
	if(result >= 0)
	{
		printf("First Rob is in %d\n", result);
	}
	else
		printf("Failed searching\n");

	printf("\nSearching second Rob\n");
	result = strlist_search(l, s1, 1);
	if(result >= 0)
	{
		printf("Second Rob is in %d\n", result);
	}
	else
		printf("Failed searching\n");

	//task3
	printf("\n");
	strlist_print(l);
	char * s;
	printf("\nRemoving 1st element\n");
	result = strlist_remove(l, 0, &s);
	if(result)
	{
		printf("%s is removed\n", s);
	}
	else
	{
		printf("Failed removing\n");
	}
	strlist_print(l);
	printf("\nRemoving 10th element\n");
	result = strlist_remove(l, 9, &s);
	if(result)
	{
		printf("%s is removed\n", s);
	}
	else
	{
		printf("Failed removing\n");
	}
	strlist_print(l);
	printf("\nRemoving 6th element\n");
	result = strlist_remove(l, 5, &s);
	if(result)
	{
		printf("%s is removed\n", s);
	}
	else
	{
		printf("Failed removing\n");
	}
	strlist_print(l);
	strlist_free(l) ;

	return 0 ;
}
