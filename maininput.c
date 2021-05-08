#include <stdio.h>
#include <stdlib.h>

#include "prelims.h"

/////////////task 3 /////////
int task3sort(const void *a, const void *b)  {   return ((*((person **)b))->status - (*((person **)a))->status);  }
/////// end of task 3 //////////////////

int main()
{
    int N, M, K; //N , M , K, denoting number of stations, number of
                 //roads, number of people respectively

    int index;         // variable used to refer to a person from the person array
    person **templist; // used for 3rd subtask o task-3 , can be used anywhere where we need to maintain a temp list,uses malloc and immediately freed after usage

    int TimeD; // this keeps track of the Time / Day in the process
    // TimeD must not take a value less than a value that has already been given
    // it should be continously increasing

    printf("Input three integers denoting number of stations, number of roads and number of people respectively...\n");
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 0; i < M; i++)
    {
        inputRoad(); //Function for taking the inputs to the stations graph. Needs to be updated (Struct station hasn't been defined properly yet).
    }
<<<<<<< HEAD

<<<<<<< HEAD
=======
  
>>>>>>> 798b64e0a41c8ba792b000423493229bb4d667ff
    person arrPerson[K]; //For storing the [ struct person ]  i.e, details about each person
    
    // taking the initial locations of each person in order 

    printf("enter the initial stations of each person in order...");
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &arrPerson[i].cur_station);
<<<<<<< HEAD
=======
    person arrPerson[K]; 

    for(int i=0;i<K;i++)
    {   
        scanf("%d",&arrPerson[i].cur_station);
>>>>>>> 947f7f56ecfb107188e4b8bf8a095e7f48ae9b31
=======
>>>>>>> 798b64e0a41c8ba792b000423493229bb4d667ff
    }

    int selectTask = -1;

    printf("Choose 1, 2 or 3 for the first, second and third tasks respectively. Press 0 to exit\n");

    while (selectTask != 0) //0 would be used to exit from the program.
    {
        scanf("%d", &selectTask); // selecting task

        if (selectTask == 1)   
        {
            printf("Type in the current day, number of people who tested positive and the number of days upto which we'd classify people as primary or secondary contacts.\n");

            int D, numPositive, X;
            scanf("%d %d %d", &D, &numPositive, &X);

            int listPostive[numPositive];

            printf("Type in the List L, i.e., the indices of the people who tested positive.\n");

            for (int i = 0; i < numPositive; i++)
            {
                scanf("%d", &listPostive[i]);
            }

<<<<<<< HEAD
            Task1(listPostive,numPositive,arrPerson,X,D,K); //Needs to be defined.
=======
            Task1(listPostive, X, D); //Needs to be defined.
>>>>>>> f707e5edfd2c562f98d3cc42a398b345e9c06a9e
        }

        if (selectTask == 2) 
        {
            inputTask2();
        }

        if (selectTask == 3)   //  other queries ( as mentioned in the pdf )
        {
            int selectTask3;
            printf("Choose\n 1 for status of a person\n 2 for location of a person\n 3 for status info at station S\n Press 0 to choose another task\n");
            scanf("%d", &selectTask3);

            if (selectTask3 == 1) // person status
            {
                index; // indexing starts from 0

                printf("enter DAY and INDEX\n");
                scanf("%d %d", &TimeD, &index);

                if ((TimeD < arrPerson[index].day))
                {
                    printf("error: DAY should not be less than the status alloted day\n");
                }
                else
                {

                    if (arrPerson[index].status == 3)
                    {

                        if ((TimeD - arrPerson[index].day) > 14)
                        {
                            printf("negative\n");
                        }
                        else
                        {
                            printf("positive\n");
                        }
                    }

                    else
                    { // print in words

                        switch (arrPerson[index].status)
                        {

                        case 0:
                            printf("negative\n");
                            break;
                        case 1:
                            printf("secondary contact\n");
                            break;
                        case 2:
                            printf("primary contact\n");
                            break;
                        }
                    }
                }
            }

            if (selectTask3 == 2) // location of person
            {
                index; // indexing starts from 0
                printf("enter the index of the person from 0 to %d\n", (K - 1));
                scanf("%d", &index); // index of a person is the index of the [struct person] in the persons array "arrPerson"

                printf("current station is %d\n", arrPerson[index].cur_station); // gives the station in which the person currently is in
            }

            if (selectTask3 == 3) // +ve/primary/secondary//-ve persons in that station
            {
                int station; // indexing start from 0  , doesn't affect task 3

                printf("enter Day and station no from 0 to %d\n", (N - 1));
                scanf("%d %d", &TimeD, &station); // always input the latest date  ( past values are not )

                templist = (person **)malloc(K * sizeof(person *));

                index = 0; // indexing starts from 0

                for (int i = 0; i < K; i++)
                {

                    if (arrPerson[i].cur_station == station)
                    {

                        templist[index] = &arrPerson[i];

                        if (templist[index]->status == 3)
                        {
                            if (TimeD - templist[index]->day > 14)
                            {
                                templist[index]->status = 0;
                            }
                        }

                        index++;
                    }
                }

                qsort(templist, index, sizeof(person *), task3sort);

                // printing templist

                for (int i = 0; i < index; i++)
                {

                    printf("%ld ", (templist[i] - arrPerson));
                    if (TimeD < templist[i]->day)
                    {
                        printf("error: DAY should not be less than the status alloted day\n");
                    }
                    else
                    {
                        switch (templist[i]->status)
                        {

                        case 0:
                            printf("negative\n");
                            break;
                        case 1:
                            printf("secondary contact\n");
                            break;
                        case 2:
                            printf("primary contact\n");
                            break;
                        case 3:

                            printf("positive\n");

                            break;
                        }
                    }
                }

                // freeing the memory allocated to templist dynamic array
                free(templist);
            }

            //No need to add condition for selectTask3==0.
        }

        /*if (selectTask == 4)  /// used to start from a random case
            { 

                printf("enter the stations , status , day of each person in order...\n");
                for (int i = 0; i < K; i++)
                {
                    scanf("%d %d %d", &arrPerson[i].cur_station, &arrPerson[i].status, &arrPerson[i].day);
                }
            }
        */
    }

    return 0;
}
