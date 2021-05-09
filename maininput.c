#include <stdio.h>
#include <stdlib.h>

#include "prelims.h"
#include "Stations.h"
#include "dynamicheap.h"

/////////////task 3 /////////
int task3sort(const void *a, const void *b)  {   return ((*((person **)b))->status - (*((person **)a))->status);  }
/////// end of task 3 //////////////////

//task2//
void DijkstraQ2(int starting,int ending,StructStations *StationGraph);

struct StnForDijkstra
{
    double danger;
    int prev;
    bool DangerConfirm;
};
typedef struct StnForDijkstra StnForDijkstra;

//end//






int main()
{
    int N, M, K; //N , M , K, denoting number of stations, number of
                 //roads, number of people respectively

    int index;         // variable used to refer to a person from the person array
    person **templist; // used for 3rd subtask o task-3 , can be used anywhere where we need to maintain a temp list,uses malloc and immediately freed after usage

    int TimeD; // this keeps track of the Time / Day in the process
    // TimeD must not take a value less than a value that has already been given
    // it should be continously increasing

    //Task2 variables
    int PID, starting, ending;
    StructStations StationGraph;
    StationGraph.NumOfStations = N;
    StationGraph.Stations = (StationNode*)malloc(sizeof(StationNode)*N);



    printf("Input three integers denoting number of stations, number of roads and number of people respectively...\n");
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 0; i < M; i++)
    {
        inputRoad(); //Function for taking the inputs to the stations graph. Needs to be updated (Struct station hasn't been defined properly yet).
    }
    person arrPerson[K]; //For storing the [ struct person ]  i.e, details about each person
    
    // taking the initial locations of each person in order 

    printf("enter the initial stations of each person in order...");
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &arrPerson[i].cur_station);
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

            Task1(listPostive,numPositive,arrPerson,X,D,K); //Needs to be defined.
        }

        if (selectTask == 2) 
        {
            printf("Enter Day number and person ID: ");
            scanf("%d%d",&TimeD,&PID);
            
            if(InQuarantine(TimeD,PID,arrPerson) == true)
                printf("Person is under Quarantine. Cannot travel\n");
            else
            {
                starting = arrPerson[PID].cur_station;     
                printf("Enter destination station number: ");
                scanf("%d",&ending);
                DijkstraQ2(starting,ending,&StationGraph);
            }
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

    free(StationGraph.Stations);

    return 0;
}


void DijkstraQ2(int starting,int ending,StructStations *StationGraph)
{
    int BestPaths[3][StationGraph->NumOfStations];       //stores the bestpaths from starting to ending station
    BestPaths[0][0] = -1;                               //the first column will hold number of stations in path
    BestPaths[1][0] = -1;
    BestPaths[2][0] = -1;
    double BestDangerValues[3];
    

    int DangerousStartIndex = -1;         //Index of most dangerous station in previous path
    int DangerousEndIndex = -1;           //relavant only after first iteration

    int DangerousStart2 = -1;           
    int DangerousEnd2 = -1;

    for(int count = 0; count <3; count++)
    {
        int NumStnConfirm = 0;

        StnForDijkstra DijkstraArr[StationGraph->NumOfStations];
        for(int i=0; i<StationGraph->NumOfStations; i++)
        {
            DijkstraArr[i].danger = -1;
            DijkstraArr[i].prev = -1;
            DijkstraArr[i].DangerConfirm = false;
        }

        heap *PathPriorityQ = init(StationGraph->NumOfStations/2);     //NumStations/2 just arbitrarily

        DijkstraArr[starting].danger = 0;
        DijkstraArr[starting].prev = starting;
        NumStnConfirm++;

        for(int i=0; i<StationGraph->Stations[starting].StnDanger.cur; i++)
        {
            int index = StationGraph->Stations[starting].StnDanger.a[0][i];

            //Ignoring the heaviest edge of previous path
            if(DangerousStartIndex == starting && DangerousEndIndex == index)
                continue;

            DijkstraArr[index].danger = StationGraph->Stations[starting].StnDanger.a[1][i];
            DijkstraArr[index].prev = starting;
    

            //adding to Priority Queue
            pair *temp = (pair*)malloc(sizeof(pair));
            temp->danger = StationGraph->Stations[starting].StnDanger.a[1][i];
            temp->ind = index; 
            push(PathPriorityQ,*temp);
        }


        while (1)
        {
            pair minPath = ExtractMin(PathPriorityQ);
            int current = minPath.ind;

            //Queue empty
            if(current == -1)
                break;   


            //All stations have already least danger path
            if(NumStnConfirm == StationGraph->NumOfStations)
                break;

            //This station has already been visited
            if(DijkstraArr[current].DangerConfirm == true)
                continue;

            DijkstraArr[current].DangerConfirm = true;
            NumStnConfirm++;

            //traversing through current station's adjacency list
            for(int i=0; i<StationGraph->Stations[current].StnDanger.cur; i++)
            {
                int index = StationGraph->Stations[current].StnDanger.a[0][i];
                double indDanger = StationGraph->Stations[current].StnDanger.a[1][i];
                
                //skipping heaviest edge
                if(current == DangerousStartIndex && index == DangerousEndIndex)
                    continue;

                if(DijkstraArr[index].DangerConfirm == true)
                    continue;

                if((DijkstraArr[index].danger > DijkstraArr[current].danger + indDanger) || DijkstraArr[index].danger == -1)
                {
                    DijkstraArr[index].danger = indDanger + DijkstraArr[current].danger;
                    DijkstraArr[index].prev = current;

                    pair *temp = (pair*)malloc(sizeof(pair));
                    temp->danger = indDanger;
                    temp->ind = index;

                    push(PathPriorityQ,*temp);
                }
            }
        }

        //No route exists from starting to ending station
        if(DijkstraArr[ending].danger == -1)
            break;
        
        BestDangerValues[count] = DijkstraArr[ending].danger;

        double DangerousEdge = -1;

        int pathtemp = ending;
        int idk = 1;
        while (pathtemp != starting)
        {
            if(DijkstraArr[pathtemp].danger > DangerousEdge)
            {
                DangerousEndIndex = pathtemp;
                DangerousStartIndex = DijkstraArr[pathtemp].prev;
                DangerousEdge = DijkstraArr[pathtemp].danger;
            }
            
            //adding path in array but in reverse order
            BestPaths[count][idk] = pathtemp;
            idk++;

            pathtemp = DijkstraArr[pathtemp].prev;
        }
        BestPaths[count][idk] = starting;
        BestPaths[count][0] = idk;
    }  


    //reverse order of paths
    for(int i=0; i<3; i++)
    {
        for(int j=1; j<=BestPaths[i][0]/2; j++)
        {
            int temp = BestPaths[i][j];
            BestPaths[i][j] = BestPaths[i][BestPaths[i][0] - j + 1];
            BestPaths[i][BestPaths[i][0] - j + 1] = temp;
        }
    }


    //Need to sort the paths based on length if danger values are equal
    //yet to do

    for(int i=0; i<3; i++)
    {
        if(BestPaths[i][0] == -1)
            break;
        printf("Path %d\n",i);
        printf("Danger Value: %ld\n",BestDangerValues[i]);
        printf("Path:\n");
        for(int j = 1; j< BestPaths[i][0]; j++ )
            printf("%d<--",BestPaths[i][j]);
        printf("%d\n\n",BestPaths[i][BestPaths[i][0]]);
    }
    
    char ch;
    do
    {
        printf("Do you want to travel? (y/n)\n");
        scanf("%c",&ch);
    }while(ch != 'y' || ch!= 'Y' || ch != 'n' || ch != 'N');

    int x;

    if(ch == 'n' || ch == 'N')
    {
        printf("Good Choice! Dont travel unnecesarily. Stay home Stay safe!\n\n");
        return 0;   //exit from Q2
    }
    else
    {
        bool flag = true;
        do 
        {
            printf("Choose which path you want to take:\n");
            scanf("%d",&x);
            x--; 
            if(x > 2 || BestPaths[x][0] == -1)
                printf("Invalid\n");
            else flag = false;
        }while(flag);
    }
}

/*
1. Taking input for stngraph
2. heaviest edge no2
3. update the meet list
4. Testing
*/