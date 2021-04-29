#include <stdio.h>
#include <string.h>

#include "heap.h"

int main ( ) { 

    
    int n = 0,N=0;
    scanf ( "%d" , &n);
    N = n;
    char func[10] = { 0 };
    double minheap[n];

    for ( int i = 0 ; i < n; i++ ) { 
        scanf( "%lf", &minheap[i]);
    }

    while (1) { 

        scanf ( "%s", func ) ;

        if ( strcmp( func , "end") == 0 ) { 
            return 0;
        }

        if ( strcmp ( func, "remroot") == 0 ) {   // removes the root and stores it at the end of the sub-array

            if ( n == 0) { 
                printf("nothing to remove....array is already sorted  ");
            }
            else{
            remove_root( minheap , n );
            n--;
            }
            
        }
        if ( strcmp ( func , "hfy") == 0)  {     // hfy stands for heapify

            heapify( minheap , n );

        }  

        if ( strcmp( func , "sort") == 0 ) { 
            heapsort( minheap , n);
        }

        printheap ( minheap , N);
    }

    return 0;



}