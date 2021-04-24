#ifndef __VEC_H_
#define __VEC_H_

typedef struct vec{
    int *a[2]; //First element is person's ID, second is day they met.
    int cap;
    int cur;
}vec;

void init(vec *v);
int resize(vec *v, int c);
int pb(vec *v, int val);
int set(vec *v, int in, int val);
int get(vec *v, int in, int val);
int del(vec *v, int in);
int fr(vec *v);

#endif