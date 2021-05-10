#include "Stations.h"
#include <stdio.h>
#include <stdlib.h>

double CalculateDangerValue(StationNode* Stn)   //Calculates danger value accoring to the given formula
{
    double DangerVal = Stn->NumOfPositive + ((double)Stn->NumOfPrimary)/5 + ((double)Stn->NUmOfSecondary)/10;
    return DangerVal;
}

void CreateStationsGraph(StructStations *GraphOfStations, int NumOfStations)    //Used to initialise the graph for stations
{
    GraphOfStations->NumOfStations = NumOfStations;
    GraphOfStations->Stations = (StationNode*)malloc(NumOfStations*sizeof(StationNode));
    for(int i=0; i<NumOfStations; i++)
    {
        init_vec(&(GraphOfStations->Stations[i].StnLength));    //Initialising vector
        init_vec(&(GraphOfStations->Stations[i].StnDanger));
    }
}

void UpdateStnLength(int U, int V, double W, StructStations *GraphOfStations)   //Given input of the starting and ending stations and the distance, it is updated in the station node of both the stations
{
    //assumes that stations U and V exist. so do check before passing

    double arr[2];
    arr[0] = V;
    arr[1] = W;
    
    pb_vec(&((GraphOfStations->Stations[U]).StnLength),arr);

    arr[0] = U;
    pb_vec(&((GraphOfStations->Stations[V]).StnLength),arr);
}