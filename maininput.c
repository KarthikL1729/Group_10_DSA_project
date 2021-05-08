#include<stdio.h>

int main()
{
    int N,M,K; //N , M , K, denoting number of stations, number of
               //roads, number of people respectively

    printf("Input three integers denoting number of stations, number of roads and number of people respectively\n");
    scanf("%d %d %d",&N, &M, &K);

    for(int i=0;i<M;i++)
    {
        inputRoad();     //Function for taking the inputs to the stations graph. Needs to be updated (Struct station hasn't been defined properly yet).
    }

    person arrPerson[K]; 

    for(int i=0;i<K;i++)
    {   
        scanf("%d",&arrPerson[i].cur_station);
    }

    int selectTask=-1;

    printf("Choose 1, 2 or 3 for the first, second and third tasks respectively. Press 0 to exit\n");

    while(selectTask!=0) //0 would be used to exit from the program.
    {
        scanf("%d",&selectTask);

        if(selectTask == 1)
        {
            printf("Type in the current day, number of people who tested positive and the number of days upto which we'd classify people as primary or secondary contacts.\n");
           
            int D,numPositive,X;
            scanf("%d %d %d",&D,&numPositive,&X);

            int listPostive[numPositive];

            printf("Type in the List L, i.e., the indices of the people who tested positive.\n");

            for(int i=0;i<numPositive;i++)
            {
                scanf("%d",&listPostive[i]);
            }

            Task1(listPostive,X,D); //Needs to be defined.
        }

        if(selectTask == 2)
        {
            inputTask2();
        }

        if(selectTask == 3)
        {
            int selectTask3;
            printf("Choose 1 for status of a person\n 2 for location of a person\n 3 for the list of covid positive, primary contacts, secondary contacts at station S\n Press 0 to choose another task\n");
            scanf("%d", &selectTask3);

            if(selectTask3==1)
            {
                int index;
                scanf("%d",&index);

                printf("%d",arrPerson[index].status); //0 is negative, 1 is primary, 2 is secondary, and 3 is positive.
            }

            if(selectTask3==2)
            {
                int index;
                scanf("%d",&index);

                printf("%d",arrPerson[index].cur_station); 
            }

            if(selectTask3==3)
            {
                int station;
                scanf("%d",&station);
                infoStation(station); //Needs to be defined.
            }
            
            //No need to add condition for selectTask3==0.
        }
        
    }

}