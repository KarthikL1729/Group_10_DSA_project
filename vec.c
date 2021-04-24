#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "vec.h"

#define SIZE 4

void init(vec *v)
{
    v->a = (int *)malloc(sizeof(int)*SIZE);
    v->cap = SIZE;
    v->cur = 0;
    //printf("HERE\n");
}

int resize(vec *v, int c)
{
    //printf("HEREB\n");
    int *x = (int *)realloc(v->a, sizeof(int) * c);
    //printf("Resizing\n");
    if(x)
    {
        v->a = x;
        v->cap = c;
        return 0;
    }
    return -1;
}

int pb(vec *v, int val)
{
    if(v->cap == v->cur)
    {
        //printf("Whytf\n");
        resize(v, v->cap*2);
    }
    v->a[v->cur++] = val;
    return 0;
}

int set(vec *v, int in, int val)
{
    if(in >= 0 && in < v->cur)
    {
        v->a[in] = val;
    }
    return 0;
}

int get(vec *v, int in, int val)
{
    if(in >=0 && in < v->cur)
    {
        return v->a[in];
    }
    return -1;
}

int del(vec *v, int in)
{
    int i = 0;
    v->a[in] = 0;
    for(i = in; i < v->cur - 1; i++)
    {
        v->a[i] = v->a[i+1];
        v->a[i+1] = 0;
    }

    v->cur--;

    if(v->cur == v->cap/4)
    {
        resize(v, v->cap/2);
    }

    return 0;
}
int fr(vec *v)
{
    free(v->a);
    v->a = NULL;
    return 0;
}

