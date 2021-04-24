#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include "vec.h"
int main()
{
    vec v;
    init(&v);
    int n;
    //printf("HEy\n");
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        //printf("Wha\n");
        int t;
        scanf("%d", &t);
        pb(&v, t);
        //printf("%d\n", v.a[i]);
    }
    for(int i = 0; i < v.cur; i++)
    {
        printf("%d ", v.a[i]);
    }
    printf("\n");
    return 0;
}