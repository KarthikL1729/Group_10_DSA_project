#include<stdio.h>
#include "prelims.h"


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