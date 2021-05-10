#include <stdio.h>
#include <stdlib.h>
#include "prelims.h"
#include "vec.h"
#include "Stations.h"
#include "dynamicheap.h"

/////////////task 3 /////////
int task3sort(const void *a, const void *b) { return ((*((person **)b))->status - (*((person **)a))->status); }
/////// end of task 3 //////////////////

//task2//

int *DijkstraQ2(int starting, int ending, StructStations *StationGraph);

//void inputRoad(int M, StructStations StationGraph);

void inputRoad(int M, StructStations *StationGraph)
{
    for (int i = 0; i < StationGraph->NumOfStations; i++)   //Initialising data members of the structure
    {
        init_vec(&StationGraph->Stations[i].StnLength);
        init_vec(&StationGraph->Stations[i].StnDanger);
        StationGraph->Stations[i].DangerValue = 0;
        StationGraph->Stations[i].NumOfPositive = 0;
        StationGraph->Stations[i].NumOfPrimary = 0;
        StationGraph->Stations[i].NUmOfSecondary = 0;
    }

    // inputs are U ,V and W
    double u[2] = {0}, v[2] = {0};
    for (int i = 0; i < M; i++)
    {

        scanf("%lf %lf %lf", &u[0], &v[0], &v[1]);  //Take input for U, V and W
        u[1] = v[1];
        pb_vec(&(*StationGraph).Stations[(int)u[0]].StnLength, v);  //Pushing back 
        pb_vec(&(*StationGraph).Stations[(int)v[0]].StnLength, u);

        u[1] = v[1] = 0;
        pb_vec(&(*StationGraph).Stations[(int)u[0]].StnDanger, v);
        pb_vec(&(*StationGraph).Stations[(int)v[0]].StnDanger, u);
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

void initialMeet(person *arrPerson, int K)  //This initialises the meet list for the people on day 0, for the people they meet in their stations
{
    double p1[2] = {0, 0};
    // O(k^2)
    for (int i = 0; i < K; i++)
    {
        arrPerson[i].status = 0;
        init_vec(&arrPerson[i].meet);

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

void printMeetList(person *arrPerson, int K)  //Can be used by giving 5 as input in the menu, prints the current meet list
{

    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < arrPerson[i].meet.cur; j++)
        {

            printf("%d %.0lf %.0lf\n", i, arrPerson[i].meet.a[0][j], arrPerson[i].meet.a[1][j]);
        }
    }
}

void Task1(int listPositive[], int numPositive, person *arrPerson, int X, int D, int K) //Task 1, making the people positive depending on the list and updating everyone's status
{
    //listPositive is an array containing the indices of people who tested positive, numPositive is the number of people who tested positive,
    //arrPerson is the array containing all the people, D is the current day and X is the number of days upto which we'd classify people as primary or secondary contacts.
    //K is the total number of people.
    for (int i = 0; i < numPositive; i++)
    {
        arrPerson[listPositive[i]].status = 3;
        arrPerson[listPositive[i]].day = D;

        if (arrPerson[listPositive[i]].meet.cur == 0)   //Empty meet list condition
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

                        printf("Primary Contact of %d : %.0lf \n", listPositive[i], arrPerson[listPositive[i]].meet.a[0][k]); //Prints the primary contact

                        if (arrPerson[(int)arrPerson[listPositive[i]].meet.a[0][k]].meet.cur == 1)
                        {
                            printf("No secondary contacts from this Primary Contact");  //Empty meet list condition
                        }
                        else
                        {
                            printf("His/Her Secondary Contacts from this Primary Contact are : ");  //Prints the secondary contacts WITH RESPECT TO the primary contact

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

struct StnForDijkstra   //STructure used specifically for Dijkstra's algorithm
{
    double danger;
    int prev;
    bool DangerConfirm;
};
typedef struct StnForDijkstra StnForDijkstra;

//This will return the length to end station in the adj list
double RetLength(vec Adj, int end)  //Returns the length of an edge depending on input, used in Dijkstra 
{
    for (int i = 0; i < Adj.cur; i++)
        if (Adj.a[0][i] == end)
            return Adj.a[1][i];
}

//This function updates the meet list of all the people whom PID met on the way.
//It goes through the whole persons array and keeps comparing.
//It is an O(N*K)worst case. basically order of Number of people * Number of stations in the path.
void UpdateMeet(int *PathArr, int PID, person *PersonArr, int NumOfPersons, int day);

void UpdateStatGraph(StructStations *StationGraph, person *arrPerson, int K)
{

    for(int i = 0; i < StationGraph->NumOfStations; i++)    //Initialising everything to zero, starting calculations from 0 too
    {
        StationGraph->Stations[i].DangerValue = 0;
        StationGraph->Stations[i].NumOfPositive = 0;
        StationGraph->Stations[i].NumOfPrimary = 0;
        StationGraph->Stations[i].NUmOfSecondary = 0;
    }
    //O(k)
    for (int i = 0; i < K; i++) //Updating the counters 
    {

        if (arrPerson[i].status == 3)
        {
            StationGraph->Stations[arrPerson[i].cur_station].NumOfPositive++;
        }
        else if (arrPerson[i].status == 2)
        {
            StationGraph->Stations[arrPerson[i].cur_station].NumOfPrimary++;
        }
        else if (arrPerson[i].status == 1)
        {
            StationGraph->Stations[arrPerson[i].cur_station].NUmOfSecondary++;
        }
    }

    for (int i = 0; i < StationGraph->NumOfStations; i++)   //Updating danger values of stations
    {
        StationGraph->Stations[i].DangerValue = CalculateDangerValue(&StationGraph->Stations[i]);
    }

    for (int i = 0; i < StationGraph->NumOfStations; i++)
    {

        for (int j = 0; j < StationGraph->Stations[i].StnDanger.cur; j++)   //Updating station danger vector
        {
            StationGraph->Stations[i].StnDanger.a[1][j] = StationGraph->Stations[(int)StationGraph->Stations[i].StnDanger.a[0][j]].DangerValue;
        }
    }
}

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

    //printMeetList(arrPerson, K);

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

        if (selectTask == 2)
        {

            printf("Enter Day number and person ID: ");
            scanf("%d%d", &TimeD, &PID);

            UpdateStatGraph(&StationGraph, arrPerson, K);
            if (InQuarantine(TimeD, PID, arrPerson) == true)
                printf("Person is under Quarantine. Cannot travel\n");
            else
            {
                starting = arrPerson[PID].cur_station;
                printf("Enter destination station number: ");

                scanf("%d", &ending);
                int *ptr = DijkstraQ2(starting, ending, &StationGraph);
                if (*ptr == -1)
                {
                    ;
                    //Person doesn't want to travel.
                    //Do nothing
                }
                else
                {
                    UpdateMeet(ptr, PID, arrPerson, K, TimeD);
                    arrPerson[PID].cur_station = ending;
                }

                //End of task 2
            }
        }

        if (selectTask == 3) //  other queries ( as mentioned in the pdf )
        {
            int selectTask3;
            printf("Choose\n 1 for status of a person\n 2 for location of a person\n 3 for status info at station S\n Press 0 to choose another task\n");
            scanf("%d", &selectTask3);

            if (selectTask3 == 1) // person status
            {
                index = 0; // indexing starts from 0

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
                index = 0; // indexing starts from 0
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

        /*if (selectTask == 4)   //used to start from a random case, only debugging
            { 

                printf("enter the stations , status , day of each person in order...\n");
                for (int i = 0; i < K; i++)
                {
                    scanf("%d %d %d", &arrPerson[i].cur_station, &arrPerson[i].status, &arrPerson[i].day);
                }
            }
            */
        if (selectTask == 5)    //Bonus task 5, printing meet list with day of meeting
        {
            printMeetList(arrPerson, K);
        }
    }

    free(StationGraph.Stations);
    free(arrPerson);

    return 0;
}

int *DijkstraQ2(int starting, int ending, StructStations *StationGraph)

{
    int BestPaths[3][StationGraph->NumOfStations]; //stores the bestpaths from starting to ending station
    BestPaths[0][0] = -1;                          //the first column will hold number of stations in path
    BestPaths[1][0] = -1;
    BestPaths[2][0] = -1;
    double BestDangerValues[3] = {-1, -1, -1};

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

            //Ignoring the heaviest edge of the 1st path and the second path (when relevant)
            if ((DangerousStartIndex == starting && DangerousEndIndex == index) || (DangerousStart2 == starting && DangerousEnd2 == index))
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

                if ((current == DangerousStartIndex && index == DangerousEndIndex) || (DangerousStart2 == current && DangerousEnd2 == index))
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

        DangerousStart2 = DangerousStartIndex;
        DangerousEnd2 = DangerousEndIndex;

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

    int best1 = 0, best2 = 1, best3 = 2;

    int length1 = 0, length2 = 0, length3 = 0;
    if ((BestDangerValues[0] == BestDangerValues[1]) && (BestDangerValues[1] == BestDangerValues[2])) //all 3 equal
    {   
        //Calculating lengths of paths
        for (int i = 1; i < BestPaths[0][0]; i++)
            length1 += RetLength(StationGraph->Stations[BestPaths[0][i]].StnLength, BestPaths[0][i + 1]);
        for (int i = 1; i < BestPaths[1][0]; i++)
            length2 += RetLength(StationGraph->Stations[BestPaths[1][i]].StnLength, BestPaths[1][i + 1]);
        for (int i = 1; i < BestPaths[2][0]; i++)
            length3 += RetLength(StationGraph->Stations[BestPaths[2][i]].StnLength, BestPaths[2][i + 1]);

        //Big block to compare the lengths and sort paths accordingly in case of same danger value
        if (length1 > length2)
        {
            if (length1 > length3)
            {
                best3 = 0;
                if (length2 > length3)
                    best1 = 2;
                else
                {
                    best2 = 2;
                    best1 = 1;
                }
            }
            else
            {
                best1 = 1;
                best2 = 0;
            }
        }
        else
        {
            if (length3 < length2)
            {
                if (length3 < length1)
                {
                    best1 = 2;
                    best2 = 0;
                    best3 = 1;
                }
                else
                {
                    best1 = 0;
                    best2 = 2;
                    best3 = 1;
                }
            }
        }
    }

    if (BestDangerValues[0] == BestDangerValues[1])
    {
        //Calculating length, repeat for different condition
        for (int i = 1; i < BestPaths[0][0]; i++)
            length1 += RetLength(StationGraph->Stations[BestPaths[0][i]].StnLength, BestPaths[0][i + 1]);
        for (int i = 1; i < BestPaths[1][0]; i++)
            length2 += RetLength(StationGraph->Stations[BestPaths[1][i]].StnLength, BestPaths[1][i + 1]);

        if (length1 > length2)
        {
            best1 = 1;
            best2 = 0;
        }
    }
    if ((BestDangerValues[1] == BestDangerValues[2]) && (BestDangerValues[1] == -1))
    {
        for (int i = 1; i < BestPaths[1][0]; i++)
            length2 += RetLength(StationGraph->Stations[BestPaths[1][i]].StnLength, BestPaths[1][i + 1]);
        for (int i = 1; i < BestPaths[2][0]; i++)
            length3 += RetLength(StationGraph->Stations[BestPaths[2][i]].StnLength, BestPaths[2][i + 1]);

        if (length2 > length3)
        {
            best3 = 1;
            best2 = 2;
        }
    }

    //Printing the 3 paths:

    printf("Path %d\n", 0);
    printf("Danger Value: %lf\n", BestDangerValues[best1]);
    printf("Path:\n");
    for (int j = 1; j < BestPaths[best1][0]; j++)
        printf("%d-->", BestPaths[best1][j]);
    printf("%d\n\n", BestPaths[best1][BestPaths[best1][0]]);

    if (BestPaths[best2][0] != -1)
    {
        printf("Path %d\n", 1);
        printf("Danger Value: %lf\n", BestDangerValues[best2]);
        printf("Path:\n");
        for (int j = 1; j < BestPaths[best2][0]; j++)
            printf("%d-->", BestPaths[best2][j]);
        printf("%d\n\n", BestPaths[best2][BestPaths[best2][0]]);
    }

    if (BestPaths[best3][0] != -1)
    {
        printf("Path %d\n", 2);
        printf("Danger Value: %lf\n", BestDangerValues[best3]);
        printf("Path:\n");
        for (int j = 1; j < BestPaths[best3][0]; j++)
            printf("%d-->", BestPaths[best3][j]);
        printf("%d\n\n", BestPaths[best3][BestPaths[best3][0]]);
    }

    char ch = 0;

    printf("Do you want to travel? (y/n)\n");
    while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N' /*&& printf("invalid\n")*/)
    {
        scanf("%c", &ch);
    }

    int x;

    if (ch == 'n' || ch == 'N')
    {
        printf("Good Choice! Dont travel unnecessarily. Stay home Stay safe!\n\n");

        int *retArr = (int *)malloc(sizeof(int));
        *retArr = -1;
        return retArr;
        // return 0; //exit from Q2
    }
    else
    {
        bool flag = true;
        do
        {

            printf("Choose which path you want to take (Zero based indexing):\n");
            scanf("%d", &x);
            if (x == 0)
                x = best1;
            else if (x == 1)
                x = best2;
            else if (x == 2)
                x = best3;

            if (x > 2 || BestPaths[x][0] == -1)

                printf("Invalid\n");
            else
                flag = false;
        } while (flag);
    }

    int *retArr = (int *)malloc(sizeof(int) * (BestPaths[x][0] + 1));
    for (int i = 0; i <= BestPaths[x][0]; i++)
        retArr[i] = BestPaths[x][i];

    return retArr;
}

void UpdateMeet(int *PathArr, int PID, person *PersonArr, int NumOfPersons, int day)    //Updates meet list depending on path chosen in Dijkstra 
{
    //skipping the starting station as they should already be in the meet list
    //used as a sub routine for task 2
    for (int i = 2; i <= PathArr[0]; i++)
    {
        for (int j = 0; j < NumOfPersons; j++)
        {
            //The person is in the station
            if (PersonArr[j].cur_station == PathArr[i])
            {
                if (PersonArr[j].status == 3) //j is under quarantine
                {
                    if (day - PersonArr[j].day > 14) //if j has already been in quarantine for > 14 days, make j negative
                        PersonArr[j].status = 0;
                    else
                        continue; //Otherwise j cant be met. so skip.
                }

                //adding into meetlist of person already in the station
                double *val = (double *)malloc(sizeof(double) * 2);
                val[0] = PID;
                val[1] = day;

                if (get_vec(&(PersonArr[j].meet), val[0]) == -1)
                {
                    pb_vec(&(PersonArr[j].meet), val);
                }
                else
                {

                    set_vec(&(PersonArr[j].meet), val);
                }

                //adding into meet list of person who is travelling
                double *val2 = (double *)malloc(sizeof(double) * 2);
                val2[0] = j;
                val2[1] = day;

                if (get_vec(&(PersonArr[PID].meet), val2[0]) == -1)
                {
                    pb_vec(&(PersonArr[PID].meet), val2);
                }
                else
                {

                    set_vec(&(PersonArr[PID].meet), val2);
                }

                // setting the status of both of them to max of both
                if (PersonArr[PID].status > PersonArr[j].status)
                {
                    if (PersonArr[PID].status == 2) //PID is primary
                        PersonArr[j].status = 1;    //set to secondary
                }
                else
                {
                    if (PersonArr[j].status == 2)  //j is Primary
                        PersonArr[PID].status = 1; //set to secondary
                }
            }
        }
    }
}

//END