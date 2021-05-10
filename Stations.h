#ifndef __Stations_Header__
#define __Stations_Header__

#include "vec.h"

typedef struct StructStations StructStations; 
typedef struct StationNode StationNode;

struct StationNode
{
    // int StnNum;                 //index of the station
   
    vec StnLength;           //It should be a vector of pairs. StnLength[i] = {StnNum,Length} 
                                // It should hold station number of the connected station and the distance between them
                                //It is undirected.
    
    vec StnDanger;           //It should be a vector of pairs. StnDanger[i] = {StnNum,DangerValue} 
                                // It should hold station number and the DangerValue of the connected station  
                                //It is directed.
    
   // int NumOfPpl;               //Maintains Number of people in station. Required?  (not required )
    int NumOfPositive;          //Number of Covid Positive people
    int NumOfPrimary;           //Number of Primary Contacts
    int NUmOfSecondary;         //Number of Secondary Contacts
    double DangerValue;          //DangerValue of the station


    //int *ListOfPpl;             //Array containing index of the people currently in the station.
                                //Have to confirm if this is required or not.
};                          

double CalculateDangerValue(StationNode* Stn);      //Returns DangerValue of the station


struct StructStations
{
    int NumOfStations;          
    StationNode *Stations;      //Array of Stations
};

//Initialises the Graph of stations
void CreateStationsGraph(StructStations *GraphOfStations, int NumOfStations);  

//Given input of the starting and ending stations and the distance, it is updated in the station node of both the stations
void UpdateStnLength(int U, int V, double W, StructStations *GraphOfStations);

#endif