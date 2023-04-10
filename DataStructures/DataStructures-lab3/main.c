#include <stdio.h>
#include "gentry.h"
#include "glist.h"


void gentry_print (void * p)
{
	gentry * e = (gentry *) p ;
	printf("(%s, %d) ", e->name, e->score) ;
}
int gentry_search(void *s){
	gentry * e = (gentry *)s;
	if(e->score>700){
		return 1;
	}
	return 0;
}
//점수가 700점 이상이면 true


int main ()
{
	int result;
	glist * l ;
	l = glist_alloc(sizeof(gentry)) ;


	gentry e1 = {"Rob", 750}, e2 = {"Jack", 510}, e3 = {"Mike", 1105}, e4 = {"Paul", 720}, e5 = {"Lee", 1000}, e6 = {"Jung", 300}, e7 = {"Hong", 500};

	glist_add_first(l, &e1) ;
	glist_add_first(l, &e2) ;
	glist_add_first(l, &e3) ;
	glist_add_first(l, &e4) ;
	glist_add_first(l, &e5) ;
	glist_add_first(l, &e6) ;
	glist_add_first(l, &e7) ;

	glist_print(l, gentry_print) ;

	gentry e ; 
	glist_remove_first(l, &e) ;
	glist_print(l, gentry_print) ;
//--------------------------------------------t1
	gentry e8 = {"Den", 460};

	printf("Adding %s, %d in last...\n", e8.name, e8.score);
	result = glist_add_last(l, &e8);
	if(result == 0){
		printf("failed adding\n");
		glist_print(l, gentry_print);
	}
	else{
		printf("Adding successful\n");
		glist_print(l, gentry_print);
	}

//--------------------------------------------t2
	printf("Searching 1st elem with above 700score....\n");
	result = glist_search(l, gentry_search);
	if(result >= 0){
		printf("Found 1st elem with above 700score in %d\n", result);
	}
	else{
		printf("1st elem with above 700score not found\n");
	}




//--------------------------------------------t3
	printf("Removing 1st elem....\n");
	result = glist_remove(l, 0, &e);
	if(result == 1){
		printf("Successfully removed\n");
	}
	else{
		printf("Removing failed\n");
	}
	glist_print(l, gentry_print);

	printf("Removing 6th elem....\n");
	result = glist_remove(l, 5, &e);
	if(result == 1){
		printf("Successfully removed\n");
	}
	else{
		printf("Removing failed\n");
	}
	glist_print(l, gentry_print);

	printf("Removing 10th elem....\n");
	result = glist_remove(l, 9, &e);
	if(result == 1){
		printf("Successfully removed\n");
	}
	else{
		printf("Removing failed\n");
	}

	glist_print(l, gentry_print);
	glist_free(l) ;

	return 0 ;
}
