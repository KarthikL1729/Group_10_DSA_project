#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vec.h"

typedef struct person{
    // int id ;  use the index of the person in the  array instead 
    vec meet; //
    /*No secondary vector, as the primary vector of 
    primary contacts will essentially be the secondary vector.*/
    int status; //0 is negative, 1 is secondary, 2 is primary, and 3 is positive. 
    /*Will update status according to the day given.
        Not completely clear yet*/
    int day;  // Day he/she tested positive, initially will be -1.  ( or day when the person got his latest status )
    int cur_station; //current station
}person;


bool InQuarantine(int day, int PID, person *arrPerson)
{
    if(arrPerson[PID].status == 3)  //positive
    {
        if(day - arrPerson[PID].day >14)
            return false;
        else 
            return true;
    }
    else 
        return false;
}

//person arr[];

