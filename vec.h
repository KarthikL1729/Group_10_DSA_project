#ifndef __VEC_H_
#define __VEC_H_

typedef struct vec{
    double *a[2]; //First element is person's ID, second is day they met.
               //First element is Station numger second is the length/ DangerVal
    int cap;
    int cur;
}vec;

void init_vec(vec *v);  //initialises the vector
int resize_vec(vec *v, int c);  
void pb_vec(vec *v, double *val);   //add a pair of integers to the vector
void set_vec(vec *v, double *val);  //updates value of a present pair
double get_vec(vec *v, double in);   //returns the second element of the pair if we pass the first element
void del_vec(vec *v, double ToDelete);    //deletes vector element based on first element 
int fr_vec(vec *v);

#endif