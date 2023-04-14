//pa2
//21900604 Lee Heejun
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "stack.h"

char s1[32], s2[32];

typedef struct
{
    int start, end;
}s_e;

void print_s_e (void * p)
{
	s_e * se = (s_e *) p ;
	printf("reverse %d to %d ", se->start, se->end) ;
}

void find_sol()
{
    if(strlen(s1) != strlen(s2))
    {
        printf("no solution\n");
        return;
    }

    stack * string = stack_alloc(sizeof(char));
    stack * s_es = stack_alloc(sizeof(s_e));

    int idx = 0;
    char s3[32];
    memcpy(s3, s2, sizeof(s2));
    int len = strlen(s1);

    while (idx < len)
    {
        s_e new;
        for (int i = idx; i < len; i++)
        {
            if (!strcmp(s1, s3))
            {
                printf("Sequence of making \"%s\" to \"%s\" using Substring reverse: \n", s1, s2);
                stack_print(s_es, print_s_e);
                return;
            }

            char check = s3[i];
            stack_push(string, &check);
            stack_top(string, &check);

            if (s1[idx] == check && idx != i)
            {
                new.start = idx;
                new.end = i;
                stack_push(s_es, &new);
                for (int j = new.start; j <= new.end; j++)
                {
                    stack_pop(string, &s3[j]);
                }
                break;
            }
            else if (s1[idx] == check && idx == i)
            {
                break;
            }
        }
        idx++;
    }
    printf("no solution\n");
}

int main()
{
    scanf("%s %s", s1, s2);

    find_sol();

    return 0;
}