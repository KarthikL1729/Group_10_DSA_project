#include <stdio.h>
#include <limits.h>
#include "dynamicheap.h"
#include  <stdlib.h>

void swap(pair *a, pair *b) //Swapping pairs
{
    pair t = *a;
    *a = *b;
    *b = t;
}

heap *init(int s)  //initialising priority queue
{
    heap *minheap = (heap *)malloc(sizeof(heap));
    if (minheap != NULL)
    {
        minheap->n = 0;
        minheap->cap = s;
        minheap->arr = (pair *)malloc(sizeof(pair) * s);

        return minheap;
    }
}

int empty(heap *h)     //Returns 1 if queue is empty
{
    if (h->n == 0)
        return 1;
    else
        return 0;
}

pair top(heap *h)   //Returns the top pair
{
    return h->arr[0];
}

void move_up(heap *h, int in)   //Moves a pair up to it's position
{
    if(in == 0)
        return;
    if (h->arr[in].danger >= h->arr[(in - 1) / 2].danger)
        return;
    swap(&h->arr[in], &h->arr[(in - 1) / 2]);
    move_up(h, (in - 1) / 2); //Recursively moving up if condition is satisfied
}

void move_down(heap *h, int in) //Moves a pair down to it's position
{

    if((in*2)+2 >= h->n)
    {
        if((in*2)+1 >= h->n)
            return;
        else
        {
            if(h->arr[in].danger > h->arr[(in*2)+1].danger)
                swap(&(h->arr[in]),&(h->arr[(in*2)+1]));
            
            return;
        }
    }

    if(h->arr[in].danger > h->arr[(in*2)+1].danger || h->arr[in].danger > h->arr[(in*2)+2].danger)
    {
        if(h->arr[(in*2)+1].danger < h->arr[(in*2)+2].danger)
        {
            swap(&(h->arr[in]),&(h->arr[(in*2)+1]));
            in = (in*2)+1;
        }
        else
        {
            swap(&(h->arr[in]),&(h->arr[(in*2)+2]));
            in = in*2 +2;
        }

        move_down(h,in);
    }
}

void push(heap *h, pair a)  //Pushes a pair into the priority queue
{
    if (h->cap - h->n == 1)
    {
        h->cap *= 2;
        h->arr = (pair *)realloc(h->arr, h->cap * sizeof(pair));
    }

    h->arr[h->n] = a;
    move_up(h, h->n); //Restoring heap
    h->n++;
}

pair ExtractMin(heap *h)    //Returns the pair with least dangervalue
{
    if (empty(h))
    {
        pair *ret = (pair*)malloc(sizeof(pair));
        ret->danger = -1;
        ret->ind = -1;
        return *ret;
    }
    if (h->n == 1)
    {
        h->n--;
        return h->arr[0];
    }


    swap(&(h->arr[0]),&(h->arr[h->n-1]));
    h->n--;
    move_down(h, 0); //Restoring heap property

    return h->arr[h->n];
}

// heap *heapify(pair *a, int s, int n)
// {
//     heap *minheap = (heap *)malloc(sizeof(heap));
//     if (minheap != NULL && s >= n)
//     {
//         h->n = n;
//         h->cap = s;
//         h->a = (pair *)malloc(s * sizeof(pair));
//         for (int i = 0; i < n; i++)
//         {
//             h->a[i] = a[i];
//             move_down(h, i);
//         }

//         return heap;
//     }

//     else
//         return;
// }
