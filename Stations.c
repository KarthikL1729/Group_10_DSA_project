#include "Stations.h"

int CalculateDangerValue(StationNode Stn)
{
    float DangerVal = Stn.NumOfPositive + ((float)Stn.NumOfPrimary)/5 + ((float)Stn.NUmOfSecondary)/10;
    return DangerVal;
}

void CreateStationsGraph(StructStations *GraphOfStations, int NumOfStations)
{
    GraphOfStations->NumOfStations = NumOfStations;
    GraphOfStations->Stations = (StationNode*)malloc(NumOfStations*sizeof(StationNode));
    for(int i=0; i<NumOfStations; i++)
    {
        init_vec(&(GraphOfStations->Stations[i].StnLength));
        init_vec(&(GraphOfStations->Stations[i].StnDanger));
    }
}

void UpdateStnLength(int U, int V, int W, StructStations *GraphOfStations)
{
    //assumes that stations U and V exist. so do check before passing

    int arr[2];
    arr[0] = V;
    arr[1] = W;
    
    pb_vec(&((GraphOfStations->Stations[U]).StnLength),arr);

    arr[0] = U;
    pb_vec(&((GraphOfStations->Stations[V]).StnLength),arr);
}