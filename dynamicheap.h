#ifndef __HEAP_H_
#define __HEAP_H_

typedef struct pair
{
    double danger, ind;
} pair;

typedef struct heap
{
    int n;
    int cap;
    pair *a;
} heap;

void swap(pair *a, pair *b);
heap *init(int s);
int empty(heap *h);
pair top(heap *h);
void move_up(heap *h, int in);
void move_down(heap *h, int in);
void push(heap *heap, pair a);
void pop(heap *heap);
heap *heapify(pair *a, int s, int n);