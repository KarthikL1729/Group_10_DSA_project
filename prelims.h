#include <stdio.h>
#include <stdlib.h>

typedef struct person{
    vec meet; //
    /*No secondary vector, as the primary vector of 
    primary contacts will essentially be the secondary vector.*/
    int status; //0, is negative, 1 is primary, 2 is secondary, and 3 is positive. 
    /*Will update status according to the day given.
        Not completely clear yet*/
    int cur_station; //current station
}person;

person arr[];


// Sreeharsha , adding a comment for trial
