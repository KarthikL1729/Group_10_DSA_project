#ifndef __heaps_for_life_
#define __heaps_for_life_

 
// implementing heap using array

// ADT for  binary heaps 


// heap functions
double remove_root ( double* minheap , int n ); // maintains the heap property after removing root, storing it at the end of array
double heapify(double* minheap , int n );   // takes any list and forms a min heap with it 
int heapsort ( double* minheap , int n ) ;   // heapify +  repeated remove_root

int printheap (double* minheap , int n );  // just prints the array
// general functions if any
void swap(double* a, double *b);



/*  if heap is implemented using trees

typedef struct stnode node;
typedef node* ptr2node;
typedef double elemType;

struct stnode { 

    ptr2node left;
    ptr2node right;
    elemType data;

};
*/

#endif