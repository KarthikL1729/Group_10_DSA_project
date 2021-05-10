#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "vec.h"

#define SIZE 4

void init_vec(vec *v)   //Initialising vector, to be done whenever a new vector is declared
{
    v->a[0] = (double*)malloc(sizeof(double)*SIZE);
    v->a[1] = (double*)malloc(sizeof(double)*SIZE);
    v->cap = SIZE;
    v->cur = 0;
}

int resize_vec(vec *v, int c)   //Resizes vector when required, background
{
    double *x = (double*)realloc(v->a[0], sizeof(double)*c);
    double *y = (double*)realloc(v->a[1],sizeof(double)*c);
    if(x && y)
    {
        v->a[0] = x;
        v->a[1] = y;
        v->cap = c;
        return 0;
    }
    return -1;
}

void pb_vec(vec *v, double *val)    //Pushes back a pair in the vector
{
    if(v->cap == v->cur)
    {
        resize_vec(v, v->cap*2);
    }
    v->a[0][v->cur] = val[0];
    v->a[1][v->cur] = val[1];
    v->cur++;
}

void set_vec(vec *v, double *val)   //Modifies the value of a given element in the vector of pairs
{
    //we are searching the vector by the first element.
    int i=0;
    for(; i<v->cur; i++)
        if(v->a[0][i] == val[0])
            break;
    
    if(i<v->cur)
    {
        v->a[0][i] = val[0];
        v->a[1][i] = val[1];
    }
}

double get_vec(vec *v, double in)   //Returns the second element of the pair that matches with the requested first element
{
    //we are searching the vector by the first element.

    for(int i=0; i<v->cur; i++)
        if(v->a[0][i] == in)
            return v->a[1][i];
    
    return -1;
}
                
void del_vec(vec *v, double ToDelete)   //Deletes an element depending on the given data 
{
    //we are searching the vector by the first element.

    int i=0;
    for(; i<v->cur; i++)
        if(v->a[0][i] == ToDelete)
            break;

    if(i<v->cur)
    {
        //its enough just to swap the to be deleted element with the last and the decrement capacity
        v->a[0][i] = v->a[0][v->cur-1];
        v->a[1][i] = v->a[1][v->cur-1];
        v->cur--;
    }
    else
        return;

    if(v->cur == v->cap/4)
    {
        resize_vec(v, v->cap/2);
    }
}

int fr_vec(vec *v)  //Frees the memory
{
    free(v->a[0]);
    free(v->a[1]);
    v = NULL;
    return 0;
}

