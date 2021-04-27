#ifndef __VEC_H_
#define __VEC_H_

typedef struct vec{
    int *a[2]; //First element is person's ID, second is day they met.
               //First element is Station numger second is the length/ DangerVal
    int cap;
    int cur;
}vec;

void init(vec *v);  //initialises the vector
int resize(vec *v, int c);  
void pb(vec *v, int *val);   //add a pair of integers to the vector
void set(vec *v, int *val);  //updates value of a present pair
int get(vec *v, int in);   //returns the second element of the pair if we pass the first element
void del(vec *v, int in);    //deletes vector element based on first element 
int fr(vec *v);

#endif