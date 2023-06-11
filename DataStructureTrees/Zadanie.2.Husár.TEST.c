#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));
    int num1,num2,num3,num4,num;
    int i;

    struct node *table = NULL;
    for(i=0;i<100000000;i++)
    {
        num1=rand()%100; num2=rand()%1000;
        num3=rand()%10000; num4=rand();
        num=num1+num2*num3+num4;

        insert(&table,num);
    }
    printf("Pridane");
    return 0;
}

/* Testovanie pre RED-BLACK tree
/* int main()
{
    srand(time(0));
    int num1,num2,num3,num4,num;
    int i;

    struct node *table = NULL;
    for(i=0;i<100000000;i++)
    {
        num1=rand()%100; num2=rand()%1000;
        num3=rand()%10000; num4=rand();
        num=num1+num2*num3+num4;

        insertion(table,num);
    }
    printf("Pridane");
    return 0;
}*/
