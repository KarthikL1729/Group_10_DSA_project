/////This is just a code to test the Stations ADT so far


#include "Stations.h"
#include <stdio.h>

int main()
{
    int N,K;
    StructStations GraphOfStations;

    printf("Enter number of stations,Number of roads:");
    scanf("%d,%d",&N,&K);
    CreateStationsGraph(&GraphOfStations,N);

    printf("Enter start,end,length:\n");
    for(int i=0; i<K; i++)
    {
        int U,V;
        double W;
        l1:
        scanf("%d,%d,%lf",&U,&V,&W);
        if(U > N-1 || V > N-1)
        {
            printf("Invalid input, try again.\n");
            goto l1;
        }
        UpdateStnLength(U,V,W,&GraphOfStations);
    }


    for(int i=0; i<GraphOfStations.NumOfStations; i++)
    {
        printf("Currently, the direct stations and length from station %d are: \n",i);
        for(int j=0; j<GraphOfStations.Stations[i].StnLength.cur; j++)
            printf("%.2lf -> %.2lf units\n",GraphOfStations.Stations[i].StnLength.a[0][j],GraphOfStations.Stations[i].StnLength.a[1][j]);
        printf("\n\n");
    }
}
