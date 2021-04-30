#include <stdio.h>
#include "dynamicheap.h"

void swap(pair *a, pair *b)
{
    pair t = *a;
    *a = *b;
    *b = *t;
}

heap *init(int s)
{
    heap *minheap = (heap *)malloc(s * sizeof(heap));
    if (minheap != NULL)
    {
        minheap->n = 0;
        minheap->cap = s;
        minheap->a = (pair *)malloc(sizeof(pair) * s);

        return minheap;
    }
}

int empty(heap *h)
{
    if (h->n == 0)
        return 1;
    else
        return 0;
}

pair top(heap *h)
{
    return h->a[0];
}

void move_up(heap *h, int in)
{
    if (h->a[in].danger >= h->a[(in - 1) / 2].danger)
        return;
    swap(&h->a[in], &h->a[(in - 1) / 2])
        move_up(h, (in - 1) / 2); //Recursively moving up if condition is satisfied
}

void move_down(heap *h, int in)
{
    int mov;
    if (2 * in + 1 >= h->n)
        return;
    if (2 * in + 2 < h->n && h->a[2 * in + 2].danger > h->a[2 * in + 1].danger)
        mov = 2 * in + 2;
    else
        mov = 2 * in + 1;
    if (h->a[mov].danger > h->a[in].danger)
        return;
    swap(&h->a[in], &h->a[mov]);
    move_down(h, mov);
}

void push(heap *h, pair a)
{
    if (h->cap - h->n == 1)
    {
        h->cap *= 2;
        h->a = (pair *)realloc(h->a, h->cap * sizeof(pair));
    }

    h->a[h->n] = a;
    move_up(h, h->n); //Restoring heap
    h->n++;
}

void pop(heap *h)
{
    if (empty(h))
        return;
    if (h->n == 1)
    {
        h->a[0].danger = -INT_MAX;
        h->a[0].ind = -INT_MAX;
    }
    else
    {
        h->a[0] = h->a[h->n - 1];
    }

    h->n--;
    move_down(h, 0); //Restoring heap property
}

heap *heapify(pair *a, int s, int n)
{
    heap *minheap = (heap *)malloc(sizeof(heap));
    if (minheap != NULL && s >= n)
    {
        h->n = n;
        h->cap = s;
        h->a = (pair *)malloc(s * sizeof(pair));
        for (int i = 0; i < n; i++)
        {
            h->a[i] = a[i];
            move_down(h, i);
        }

        return heap;
    }

    else
        return;
}