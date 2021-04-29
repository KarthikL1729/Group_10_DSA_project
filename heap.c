#include <stdio.h>

#include "heap.h"


// node at i      ( indexing starts from 0)
// left child at  2i + 1 
// right child at  2i + 2
// parent at  floor( (i-1) / 2)


// minheap[0]  gives the least element


void swap(double* a, double *b) { 

    double temp = *a;
    *a = *b;
    *b = temp;
}

double remove_root ( double* minheap , int n ) { 

    int min = minheap[0];
    double last = minheap[n-1];
    int i = 1;
    int sci = 0 ; // stands for smaller child index

    minheap[0] = last;


    while ( 1 ) { 

        i = sci;

        if ( (2*i+1) < n  ) { 
            sci = 2*i + 1;
        } 
        else { break;}

        if  ((2*i+ 2) < n) { 
            if ( minheap[sci] > minheap[sci+1] ) { 
                sci = sci+1;
            }
        } 

        if ( minheap[sci] < minheap[i]) {

            swap(&minheap[sci], &minheap[i]);
            
        }
        else { 
            break;
        }
        
    
    }

    minheap[n-1] = min;
    return min;
       

}

double heapify(double* minheap , int n ) { 
    // goes from bottom to top of the heap

    int i = n-1;
    int sci = 0 ; // stands for smaller child index

    for ( int j = n-1 ; j > -1 ; j--) {
        i = j ;
     while ( 1 ) { 

        

        if ( (2*i+1) < n  ) { 
            sci = 2*i + 1;
        } 
        else { break;}

        if  ((2*i+ 2) < n) { 
            if ( minheap[sci] > minheap[sci+1] ) { 
                sci = sci+1;
            }
        } 

        if ( minheap[sci] < minheap[i]) {

            swap(&minheap[sci], &minheap[i]);
            
        }
        else { 
            break;
        }
        
        i = sci;
    
        }
    }

    
    return 0 ;
 
} 

int heapsort ( double* minheap , int n ) { 

    heapify ( minheap , n );

    for ( int i = 0 ; i < n ; i++ ) { 

        remove_root ( minheap , n-i);
         
    }

    return 0;
}


/// optional

int printheap (double* minheap , int n ) { 

    for ( int i = 0 ; i < n ; i++) {
            printf( "%.1f ", minheap[i]) ;
        }

    printf("\n");

}
