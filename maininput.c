#include <stdio.h>
#include <stdlib.h>

#include "prelims.h"

#include "vec.c"
//#include "prelims.h"
#include "Stations.h"
// #include "dynamicheap.h"

/////////////task 3 /////////
int task3sort(const void *a, const void *b) { return ((*((person **)b))->status - (*((person **)a))->status); }
/////// end of task 3 //////////////////

//task2//
//void DijkstraQ2(int starting, int ending, StructStations *StationGraph);
//void inputRoad(int M, StructStations StationGraph);

void inputRoad(int M, StructStations *StationGraph)
{

    // inputs are U ,V and W
    double u[2] = {0}, v[2] = {0};
    for (int i = 0; i < M; i++)
    {

        scanf("%lf %lf %lf", &u[0], &v[0], &v[1]);
        u[1] = v[1];

        pb_vec(&(*StationGraph).Stations[(int)u[0]].StnLength, v);
        pb_vec(&(*StationGraph).Stations[(int)v[0]].StnLength, u);
    }
}

void printstat(int N, StructStations *StationGraph) // only for debugging
{
    for (int i = 0; i < N; i++)
    {

        for (int j = 0; j < StationGraph->Stations[i].StnLength.cur; j++)
        {

            printf("%d %.0lf %.0lf\n", i, StationGraph->Stations[i].StnLength.a[0][j], StationGraph->Stations[i].StnLength.a[1][j]);
        }
    }
}

void initialMeet(person *arrPerson, int K)
{

    double p1[2] = {0, 0};
    // O(k^2)
    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < K; j++)
        {

            if (arrPerson[i].cur_station == arrPerson[j].cur_station && (i != j))
            {
                p1[0] = (double)j;
                pb_vec(&arrPerson[i].meet, p1);
            }
        }
    }
}

void printMeetList(person *arrPerson, int K)
{

    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < arrPerson[i].meet.cur; j++)
        {

            printf("%d %.0lf %.0lf\n", i, arrPerson[i].meet.a[0][j], arrPerson[i].meet.a[1][j]);
        }
    }
}

void Task1(int listPositive[], int numPositive, person *arrPerson, int X, int D, int K)
{
    //listPositive is an array containing the indices of people who tested positive, numPositive is the number of people who tested positive,
    //arrPerson is the array containing all the people, D is the current day and X is the number of days upto which we'd classify people as primary or secondary contacts.
    //K is the total number of people.
    for (int i = 0; i < numPositive; i++)
    {
        arrPerson[listPositive[i]].status = 3;
        arrPerson[listPositive[i]].day = D;

        if (arrPerson[listPositive[i]].meet.cur == 0)
        {
            printf("No Primary Contacts of Person %d\n\n", listPositive[i]);
        }
        else
        {
            for (int k = 0; k < arrPerson[listPositive[i]].meet.cur; k++)
            {

                if (listPositive[i] != (int)arrPerson[listPositive[i]].meet.a[0][k])
                {
                    if (D - (arrPerson[listPositive[i]].meet.a[1][k]) <= X)
                    {

                        if (arrPerson[(int)arrPerson[listPositive[i]].meet.a[0][k]].status < 3)
                            arrPerson[(int)arrPerson[listPositive[i]].meet.a[0][k]].status = 2;

                        printf("Primary Contact of %d : %.0lf \n", listPositive[i], arrPerson[listPositive[i]].meet.a[0][k]);

                        if (arrPerson[(int)arrPerson[listPositive[i]].meet.a[0][k]].meet.cur == 1)
                        {
                            printf("No secondary contacts from this Primary Contact");
                        }
                        else
                        {
                            printf("His/Her Secondary Contacts from this Primary Contact are : ");

                            for (int j = 0; j < arrPerson[(int)arrPerson[listPositive[i]].meet.a[0][k]].meet.cur; j++)
                            {
                                if (listPositive[i] != (int)arrPerson[(int)arrPerson[listPositive[i]].meet.a[0][k]].meet.a[0][j])
                                {
                                    if (D - (arrPerson[listPositive[i]].meet.a[1][k]) <= X)
                                    {

                                        if (arrPerson[(int)arrPerson[(int)arrPerson[listPositive[i]].meet.a[0][k]].meet.a[0][j]].status < 2)
                                            arrPerson[(int)arrPerson[(int)arrPerson[listPositive[i]].meet.a[0][k]].meet.a[0][j]].status = 1;
                                        printf("%.0lf ", arrPerson[(int)arrPerson[listPositive[i]].meet.a[0][k]].meet.a[0][j]);
                                    }
                                }
                            }
                        }
                        printf("\n\n");
                    }
                }
            }
        }
    }
}

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
    printf("Input three integers denoting number of stations, number of roads and number of people respectively...\n");
    scanf("%d %d %d", &N, &M, &K);

    int index;         // variable used to refer to a person from the person array
    person **templist; // used for 3rd subtask of task-3 , can be used anywhere where we need to maintain a temp list,uses malloc and immediately freed after usage

    int TimeD; // this keeps track of the Time / Day in the process
    // TimeD must not take a value less than a value that has already been given
    // it should be continously increasing

    //Task2 variables
    int PID, starting, ending;
    StructStations StationGraph;
    StationGraph.NumOfStations = N;
    StationGraph.Stations = (StationNode *)malloc(sizeof(StationNode) * N);

    printf("Input connections between stations U and V of length W\n");
    inputRoad(M, &StationGraph); //Function for taking the inputs to the stations graph. Needs to be updated (Struct station hasn't been defined properly yet).
    //printstat(N, &StationGraph); // only for debugging

    person *arrPerson = (person *)malloc(sizeof(person) * K); //For storing the [ struct person ]  i.e, details about each person

    // taking the initial locations of each person in order

    printf("enter the initial stations of each person in order...\n");

    for (int i = 0; i < K; i++)
    {
        scanf("%d", &arrPerson[i].cur_station);
    }

    initialMeet(arrPerson, K);
    //printMeetList(arrPerson,K);

    int selectTask = -1;

    while (selectTask != 0) //0 would be used to exit from the program.
    {

        printf("Choose 1, 2 or 3 for the first, second and third tasks respectively. Press 0 to exit\n");

        scanf("%d", &selectTask); // selecting task

        if (selectTask == 1)
        {
            printf("Type in the current day, number of people who tested positive and the number of days upto which we'd classify people as primary or secondary contacts.\n");

            int numPositive, X;
            scanf("%d %d %d", &TimeD, &numPositive, &X);

            int listPostive[numPositive];

            printf("Type in the List L, i.e., the indices of the people who tested positive.\n");

            for (int i = 0; i < numPositive; i++)
            {
                scanf("%d", &listPostive[i]);
            }

            Task1(listPostive, numPositive, arrPerson, X, TimeD, K); //Needs to be defined.
        }

        /*
        if (selectTask == 2)
        {
            printf("Enter Day number and person ID: ");
            scanf("%d%d", &TimeD, &PID);

            if (InQuarantine(TimeD, PID, arrPerson) == true)
                printf("Person is under Quarantine. Cannot travel\n");
            else
            {
                starting = arrPerson[PID].cur_station;
                printf("Enter destination station number: ");
                scanf("%d", &ending);
                DijkstraQ2(starting, ending, &StationGraph);
            }
        }
*/
        if (selectTask == 3) //  other queries ( as mentioned in the pdf )
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
    free(arrPerson);

    return 0;
}

/*
void DijkstraQ2(int starting, int ending, StructStations *StationGraph)
{
    int BestPaths[3][StationGraph->NumOfStations]; //stores the bestpaths from starting to ending station
    BestPaths[0][0] = -1;                          //the first column will hold number of stations in path
    BestPaths[1][0] = -1;
    BestPaths[2][0] = -1;
    double BestDangerValues[3];

    int DangerousStartIndex = -1; //Index of most dangerous station in previous path
    int DangerousEndIndex = -1;   //relavant only after first iteration

    int DangerousStart2 = -1;
    int DangerousEnd2 = -1;

    for (int count = 0; count < 3; count++)
    {
        int NumStnConfirm = 0;

        StnForDijkstra DijkstraArr[StationGraph->NumOfStations];
        for (int i = 0; i < StationGraph->NumOfStations; i++)
        {
            DijkstraArr[i].danger = -1;
            DijkstraArr[i].prev = -1;
            DijkstraArr[i].DangerConfirm = false;
        }

        heap *PathPriorityQ = init(StationGraph->NumOfStations / 2); //NumStations/2 just arbitrarily

        DijkstraArr[starting].danger = 0;
        DijkstraArr[starting].prev = starting;
        NumStnConfirm++;

        for (int i = 0; i < StationGraph->Stations[starting].StnDanger.cur; i++)
        {
            int index = StationGraph->Stations[starting].StnDanger.a[0][i];

            //Ignoring the heaviest edge of previous path
            if (DangerousStartIndex == starting && DangerousEndIndex == index)
                continue;

            DijkstraArr[index].danger = StationGraph->Stations[starting].StnDanger.a[1][i];
            DijkstraArr[index].prev = starting;

            //adding to Priority Queue
            pair *temp = (pair *)malloc(sizeof(pair));
            temp->danger = StationGraph->Stations[starting].StnDanger.a[1][i];
            temp->ind = index;
            push(PathPriorityQ, *temp);
        }

        while (1)
        {
            pair minPath = ExtractMin(PathPriorityQ);
            int current = minPath.ind;

            //Queue empty
            if (current == -1)
                break;

            //All stations have already least danger path
            if (NumStnConfirm == StationGraph->NumOfStations)
                break;

            //This station has already been visited
            if (DijkstraArr[current].DangerConfirm == true)
                continue;

            DijkstraArr[current].DangerConfirm = true;
            NumStnConfirm++;

            //traversing through current station's adjacency list
            for (int i = 0; i < StationGraph->Stations[current].StnDanger.cur; i++)
            {
                int index = StationGraph->Stations[current].StnDanger.a[0][i];
                double indDanger = StationGraph->Stations[current].StnDanger.a[1][i];

                //skipping heaviest edge
                if (current == DangerousStartIndex && index == DangerousEndIndex)
                    continue;

                if (DijkstraArr[index].DangerConfirm == true)
                    continue;

                if ((DijkstraArr[index].danger > DijkstraArr[current].danger + indDanger) || DijkstraArr[index].danger == -1)
                {
                    DijkstraArr[index].danger = indDanger + DijkstraArr[current].danger;
                    DijkstraArr[index].prev = current;

                    pair *temp = (pair *)malloc(sizeof(pair));
                    temp->danger = indDanger;
                    temp->ind = index;

                    push(PathPriorityQ, *temp);
                }
            }
        }

        //No route exists from starting to ending station
        if (DijkstraArr[ending].danger == -1)
            break;

        BestDangerValues[count] = DijkstraArr[ending].danger;

        double DangerousEdge = -1;

        int pathtemp = ending;
        int idk = 1;
        while (pathtemp != starting)
        {
            if (DijkstraArr[pathtemp].danger > DangerousEdge)
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
    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j <= BestPaths[i][0] / 2; j++)
        {
            int temp = BestPaths[i][j];
            BestPaths[i][j] = BestPaths[i][BestPaths[i][0] - j + 1];
            BestPaths[i][BestPaths[i][0] - j + 1] = temp;
        }
    }

    //Need to sort the paths based on length if danger values are equal
    //yet to do

    for (int i = 0; i < 3; i++)
    {
        if (BestPaths[i][0] == -1)
            break;
        printf("Path %d\n", i);
        printf("Danger Value: %ld\n", BestDangerValues[i]);
        printf("Path:\n");
        for (int j = 1; j < BestPaths[i][0]; j++)
            printf("%d<--", BestPaths[i][j]);
        printf("%d\n\n", BestPaths[i][BestPaths[i][0]]);
    }

    char ch;
    do
    {
        printf("Do you want to travel? (y/n)\n");
        scanf("%c", &ch);
    } while (ch != 'y' || ch != 'Y' || ch != 'n' || ch != 'N');

    int x;

    if (ch == 'n' || ch == 'N')
    {
        printf("Good Choice! Dont travel unnecesarily. Stay home Stay safe!\n\n");
        return 0; //exit from Q2
    }
    else
    {
        bool flag = true;
        do
        {
            printf("Choose which path you want to take:\n");
            scanf("%d", &x);
            x--;
            if (x > 2 || BestPaths[x][0] == -1)
                printf("Invalid\n");
            else
                flag = false;
        } while (flag);
    }
}

*/

/*
1. Taking input for stngraph
2. heaviest edge no2
3. update the meet list
4. Testing
*/
