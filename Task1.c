#include<stdio.h>

Task1(int listPositive[], int numPositive, person arrPerson[], int X, int D, int K)
{
    //listPositive is an array containing the indices of people who tested positive, numPositive is the number of people who tested positive,
    //arrPerson is the array containing all the people, D is the current day and X is the number of days upto which we'd classify people as primary or secondary contacts.
    //K is the total number of people.
    for(int i=0;i<numPositive;i++)
    {
        arrPerson[listPositive[i]].status = 3;
        arrPerson[listPositive[i]].day = D;
        
        for(int i=0;i<arrPerson[listPositive[i]].meet.curr;i++)
        {
            if(D-(arrPerson[listPositive[i]].meet.a[1][i]) <= X)
            {
                arrPerson[arrPerson[listPositive[i]].meet.a[0][i]].status=2;
                printf("Primary Contact : %d \n",arrPerson[listPositive[i]].meet.a[0][i]);
                printf("His Secondary Contacts are : ");
                for(int j=0;j<arrPerson[arrPerson[listPositive[i]].meet.a[0][i]].meet.curr;j++)
                {
                    arrPerson[arrPerson[arrPerson[listPositive[i]].meet.a[0][i]].meet.a[0][j]].status = 1;
                    printf("%d ",arrPerson[arrPerson[listPositive[i]].meet.a[0][i]].meet.a[0][j]);
                }
                printf("\n\n");
            }
        }
    }

}