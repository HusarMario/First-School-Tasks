#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int data;
    int filled;
    struct node *next;
};

int size = 0;       /* velkost tabulky */
int count = 0;      /* pocet zaznamov v tabulke */
void init_new_table(); /* zadefinovanie funkcie tak aby sa dala pouzit neskor a zaroven aby sa dala v nej pouzit funkcia insert*/

void init_table(struct node **table)
{
        size = size + 10000000;     /* zmena velkosti tabulky, meni sa tu */
        int i;
        struct node *create = (struct node*)malloc(size*sizeof(struct node));

        for(i=0;i<size;i++)
        {
            create[i].data=0;
            create[i].next=NULL;
            create[i].filled=0;
        }

        *table=create;
}

void insert(struct node **table,int input)
{
    struct node *search;
    search=*table;

    if(*table==NULL)        /* vytvorenie novej tabulky z prveho zaznamu */
    {
        init_table(&search);
        *table=search;
    }

    if(count>size/2)
    {
        init_new_table(&search);
        *table=search;
    }

    int calculate;          /* vypocet kluca */
    calculate=input%size;

    while(1)
    {
        if(search[calculate].filled==0)         /* pridanie na zaciatok */
        {
            search[calculate].data = input;
            search[calculate].filled = 1;

            count++;
            break;
        }

        if(search[calculate].data==input)       /* dupilkaty */
        {
            break;
        }

        if(search[calculate].next==NULL)        /* pridanie na druhe miesto */
        {
            struct node *create = (struct node*)malloc(sizeof(struct node));

            create->data=input;
            create->next=NULL;
            create->filled=1;

            search[calculate].next=create;

            count++;
            break;
        }

        search=search[calculate].next;

        if(search->data==input)         /* duplikaty */
        {
            break;
        }

        while(1)
        {
            if(search->next==NULL)      /* pridanie na posledne miesto */
            {
                struct node *create = (struct node*)malloc(sizeof(struct node));

                create->data=input;
                create->next=NULL;
                create->filled=1;

                search->next=create;

                count++;
                break;
            }

            search=search->next;

            if(search->data==input)         /* duplikaty */
            {
                break;
            }
        }

        break;
    }
}

void search(struct node **table,int input)
{
    if(*table==NULL)        /* ak tabulka este neexistuje */
    {
        printf("Neexistuje\n");
        return;
    }
    struct node *search;
    search=*table;

    int calculate;
    calculate=input%size;

    while(1)
    {
        if(search[calculate].filled==0) /* neexistuje ziadny zaznam */
        {
            printf("Neexistuje\n");
            break;
        }

        if(search[calculate].data==input)   /* nasiel sa na prvom mieste */
        {
            printf("Existuje\n");
            break;
        }

        if(search[calculate].next==NULL)    /*po prvom neexistuje dalsi zaznam */
        {
            printf("Neexistuje\n");
            break;
        }

        search=search[calculate].next;

        while(1)
        {
            if(search->data==input)     /* nasiel sa zaznam */
            {
                printf("Existuje\n");
                break;
            }

            if(search->next==NULL)      /*koniec zaznamov - nenaslo sa */
            {
                printf("Neexistuje\n");
                break;
            }

            search=search->next;
        }
        break;
    }

}

void init_new_table(struct node **table)
{
    int old_size = size;        /* stara velkost pre najdenie vsetkych prvkov */
    int i;
    int data;                   /* pomocna hodnota pri testovani.. nepotrebne da sa to priamo ale potreboval som to */
    count = 0;                  /* count sa resetuje a hodnoty sa pridavaju odznova */

    struct node *old_table;
    old_table=*table;
    struct node *find;
    struct node *new_table=NULL;

    for(i=0;i<old_size;i++)     /* nachadza vsetky stare hodnoty a pridava ich do novej tabulky */
    {
        if(old_table[i].filled==0)
        {

        }
        else
        {
            data=old_table[i].data;
            insert(&new_table,data);

            if(old_table[i].next==NULL)
            {

            }
            else
            {
                find=old_table[i].next;
                data=find->data;
                insert(&new_table,data);

                while(1)
                {
                    if(find->next==NULL)
                    {
                        break;
                    }

                    find=find->next;
                    data=find->data;
                    insert(&new_table,data);
                }
            }
        }
    }

    *table=new_table;
}



int main()
{

    return 0;
}
