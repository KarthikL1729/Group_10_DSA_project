//This file is no more required.


#include <stdio.h>
#include "prelims.h"
#include "dynamicheap.h"
#include <stdbool.h>
#include "Stations.h"
// #include <limits.h>


//This structure is just for Dijkstra algo
struct StnForDijkstra
{
    double danger;
    int prev;
    bool DangerConfirm;
};
typedef struct StnForDijkstra StnForDijkstra;

bool InQuarantine(int day, int PID, person *arrPerson)
{
    if(arrPerson[PID].status == 3)
    {
        if(arrPerson[PID].day)
    }
}



int main()
{
    StructStations StationGraph;        //This is to be removed. It will be there in the main() or global (whatever)

    int PID;                            //Person ID
    printf("Enter person ID: ");
    scanf("%d",&PID);

    printf("Enter Day number\n");
    int TimeD;
    scanf("%d",&TimeD);

    if(InQuarantine(TimeD,PID,) == true)
    {
        printf("Person is under Quarantine. Cannot travel\n");
        return 0;   //exit from the query
    }

    int starting = findStation(PID);        //This needs to return the station in which that person is currently.

    int ending;                             //destination
    printf("Enter destination station number: ");
    scanf("%d",&ending);

    // ending = ending - 1;    //if user is entering in 1 index.


    int BestPaths[3][StationGraph.NumOfStations];       //stores the bestpaths from starting to ending station
    BestPaths[0][0] = -1;                               //the first column will hold number of stations in path
    BestPaths[1][0] = -1;
    BestPaths[2][0] = -1;
    double BestDangerValues[3];
    

    int DangerousStartIndex = -1;         //Index of most dangerous station in previous path
    int DangerousEndIndex = -1;           //relavant only after first iteration

    for(int count = 0; count <3; count++)
    {
        int NumStnConfirm = 0;

        StnForDijkstra DijkstraArr[StationGraph.NumOfStations];
        for(int i=0; i<StationGraph.NumOfStations; i++)
        {
            DijkstraArr[i].danger = -1;
            DijkstraArr[i].prev = -1;
            DijkstraArr[i].DangerConfirm = false;
        }

        heap *PathPriorityQ = init(StationGraph.NumOfStations/2);     //NumStations/2 just arbitrarily

        DijkstraArr[starting].danger = 0;
        DijkstraArr[starting].prev = starting;
        NumStnConfirm++;

        for(int i=0; i<StationGraph.Stations[starting].StnDanger.cur; i++)
        {
            int index = StationGraph.Stations[starting].StnDanger.a[i][0];

            //Ignoring the heaviest edge of previous path
            if(DangerousStartIndex == 0 && DangerousEndIndex == index)
                continue;

            DijkstraArr[index].danger = StationGraph.Stations[starting].StnDanger.a[i][1];
            DijkstraArr[index].prev = starting;
    

            //adding to Priority Queue
            pair *temp = (pair*)malloc(sizeof(pair));
            temp->danger = StationGraph.Stations[starting].StnDanger.a[i][1];
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
            if(NumStnConfirm == StationGraph.NumOfStations)
                break;

            //This station has already been visited
            if(DijkstraArr[current].DangerConfirm == true)
                continue;

            DijkstraArr[current].DangerConfirm = true;
            NumStnConfirm++;

            //traversing through current station's adjacency list
            for(int i=0; i<StationGraph.Stations[current].StnDanger.cur; i++)
            {
                int index = StationGraph.Stations[current].StnDanger.a[i][0];
                double indDanger = StationGraph.Stations[current].StnDanger.a[i][1];
                
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

    //Need to visit all the stations and update the primary/secondary stuff
    //yet to do


    
    return 0;
}

//Flaws:
/*
1. In second iteration we remove most dangerous edge of 1st path
in third iteration we must remove 2 edges: the new most dangerous
edge and the original most dangerous edge.
I have only removed the new most dangerous edge
So 3rd iteration will give same path as first.

Yet to correct.
*/

//Assumptions:
/*
1. No multiple direct paths between two stations
*/