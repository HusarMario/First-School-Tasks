#include <stdio.h>
#include <string.h>

typedef struct Record
{
 char category[50+1];
 char place[50+1];
 char street[100+1];
 int area;
 int price;
 char descrp[200+1];
 struct Record *next;
}RECORD;

void n(RECORD **first,int *records)
{
    char c;
    FILE *fr;
    int loop = 0;
    int start = 0;
    int i=0;
    RECORD *last;
    *records = 0;
    RECORD *remove;

    if ((fr = fopen("reality.txt" , "r")) == NULL)
        printf("Zaznamy neboli nacitane\n");

    // // dealokovanie predchadzajuceho pola // //
    if(first==NULL)
    {

    }
    else
    {
        for(i=0;i<*records;i++)
        {
        remove=(*first);
        (*first)=(*first)->next;
        free(remove);
        }

    }

    // // zratanie zaznamov // //
    while((c=getc(fr)) != EOF)
    {
        if(c == '&')
            (*records)++;
    }
    rewind(fr);

    // // nacitanie zaznamov zo suboru // //
    while(1)
    {
        if(loop == *records)
            break;

        RECORD *create = (RECORD*) malloc(sizeof(RECORD));

        if(start == 1)
            last->next = create;

        while((c=getc(fr)) != '\n')
        {
            continue;
        }

        // // Kategoria // //
        i=0;
        while((c=getc(fr)) != '\n')
        {
            create->category[i]=c;
            i++;
        }
        if(i>=50)
            create->category[50] = '\0';
        else
            create->category[i] = '\0';

        // // Miesto // //
        i=0;
        while((c=getc(fr)) != '\n')
        {
            create->place[i]=c;
            i++;
        }
        if(i>=50)
            create->place[50] = '\0';
        else
            create->place[i] = '\0';

        // // Ulica // //
        i=0;
        while((c=getc(fr)) != '\n')
        {
            create->street[i]=c;
            i++;
        }
        if(i>=100)
            create->street[100] = '\0';
        else
            create->street[i] = '\0';

        // // Rozloha // //
        while((c=getc(fr)) != '\n')
        {
            fseek(fr,-1,SEEK_CUR);
            fscanf(fr,"%d",&create->area);
        }

        // // Cena // //
        while((c=getc(fr)) != '\n')
        {
            fseek(fr,-1,SEEK_CUR);
            fscanf(fr,"%d",&create->price);
        }

        // // Popis // //
        i=0;
        while((c=getc(fr)) != '\n')
        {
            create->descrp[i]=c;
            i++;
        }
        if(i>=200)
            create->descrp[200] = '\0';
        else
            create->descrp[i] = '\0';

        // // // // //

        create->next = NULL;

        last = create;

        if(start == 0)
        {
            *first = last;
            start = 1;
        }

        loop++;
    }


    printf("Nacitalo sa %d zaznamov\n",*records);

    fclose(fr);
}

void v(RECORD *first,int records)
{
    RECORD *read;
    int i;

    read = first;

    // // vypisanie zaznamov // //
    if(first == NULL)
    {

    }
    else
    {
        for(i=1;i<=records;i++)
        {
        printf("%d.\n",i);
        printf("kategoria ponuky: %s\n",read->category);
        printf("miesto ponuky: %s\n",read->place);
        printf("ulica: %s\n",read->street);
        printf("rozloha v m2: %d\n",read->area);
        printf("cena: %d\n",read->price);
        printf("popis: %s\n",read->descrp);

        read=read->next;
        }
    }

}

void p(RECORD **first,int *records,int position)
{
    RECORD *curr;
    RECORD *prev;
    int i = 0;

    // // vytvorenie noveho zaznamu // //
    RECORD *create = (RECORD*) malloc(sizeof(RECORD));
    scanf(" %[^\n]s",create->category);
    scanf(" %[^\n]s",create->place);
    scanf(" %[^\n]s",create->street);
    scanf("%d",&create->area);
    scanf("%d",&create->price);
    scanf(" %[^\n]s",create->descrp);
    create->next = NULL;

    // // dosadenie noveho zaznamu // //
    if((*first) == NULL)
        *first = create;

    else
    {
        if(position == 1)
        {
            curr = *first;
            create->next = curr;
            *first = create;
        }

        if((position > 1)&&(position <= *records))
        {
            curr = *first;
            for(i=1;i<position;i++)
            {
                prev = curr;
                curr = curr->next;
            }
            create->next = curr;
            prev->next = create;
        }

        if(position > *records)
        {
            curr = *first;
            for(i=1;i<*records;i++)
                curr = curr->next;
            curr->next = create;
        }
    }

    (*records)++;



}

void z(RECORD **first,int *records, char *search)
{
    RECORD *read;
    RECORD *curr;
    RECORD *prev;
    read = *first;

    int i=0;
    int j=0;

    int start=0;
    int new_records=0;

    char compare[50+1];
    char *match;

    while(search[i] != '\0')
    {
        if(((search[i])>='A') && ((search[i])<='Z'))
            search[i]=search[i]+32;

        i++;
    }
    // // vytvorenie noveho zoznamu bez zhodujucich sa zaznamov // //
    if(*first == NULL)
    {

    }
    else
    {
        (*first) = NULL;

        for(j=1;j<=(*records);j++)
        {
            strcpy(compare,read->place);
            curr=read;
            read=read->next;

            i=0;
            while(compare[i] != '\0')
            {
                if(((compare[i])>='A') && ((compare[i])<='Z'))
                    compare[i]=compare[i]+32;

                i++;
            }

            match = strstr(compare,search);

            if (match != NULL)
            {
                free(curr);
            }

            else
            {
               if(start==0)
               {
                   *first=curr;
                   (*first)->next=NULL;
                   prev=*first;
                   start=1;
               }

               else
               {
                   prev->next=curr;
                   prev=curr;
                   prev->next=NULL;
               }

               new_records++;
            }
        }
    printf("Vymazalo sa %d zaznamov\n",(*records)-new_records);

    (*records)=new_records;

    }

}

void h(RECORD *first,int records, int value)
{
    RECORD *read;
    int i=0;
    int j=1;

    int found=0;

    read = first;

    // // vypisanie zazanmov zhodoujucich sa s podmienkou // //
    if(first == NULL)
    {

    }
    else
    {
        for(i=1;i<=records;i++)
        {

        if(read->price<=value)
        {
            printf("%d.\n",j);
            printf("kategoria ponuky: %s\n",read->category);
            printf("miesto ponuky: %s\n",read->place);
            printf("ulica: %s\n",read->street);
            printf("rozloha v m2: %d\n",read->area);
            printf("cena: %d\n",read->price);
            printf("popis: %s\n",read->descrp);
            j++;
            found = 1;
        }

        read=read->next;
        }

    if(found == 0)
        printf("V ponuke su len reality s vyssou cenou\n");
    }
}

void a(RECORD *first,int records, char *search)
{
    RECORD *read;
    read = first;

    // vytvorenie noveho zaznamu // //
    RECORD *create = (RECORD*) malloc(sizeof(RECORD));
    scanf(" %[^\n]s",create->category);
    scanf(" %[^\n]s",create->place);
    scanf(" %[^\n]s",create->street);
    scanf("%d",&create->area);
    scanf("%d",&create->price);
    scanf(" %[^\n]s",create->descrp);
    create->next = NULL;

    int i=0;
    int j=0;

    int count_match=0;

    char compare[50+1];
    char *match;

    while(search[i] != '\0')
    {
        if(((search[i])>='A') && ((search[i])<='Z'))
            search[i]=search[i]+32;

        i++;
    }

    // // nahradenie zazanmov zhodujucich sa s podmienkou // //
    if(first == NULL)
    {

    }
    else
    {
        for(j=1;j<=records;j++)
        {
            strcpy(compare,read->place);

            i=0;
            while(compare[i] != '\0')
            {
                if(((compare[i])>='A') && ((compare[i])<='Z'))
                    compare[i]=compare[i]+32;

                i++;
            }

            match = strstr(compare,search);


            if (match != NULL)
            {
                strcpy(read->category,create->category);
                strcpy(read->place,create->place);
                strcpy(read->street,create->street);
                read->area=create->area;
                read->price=create->price;
                strcpy(read->descrp,create->descrp);
                count_match++;
            }

            read=read->next;
        }
    }
    printf("Aktualizovalo sa %d zaznamov\n",count_match);
    free(create);
}


int main()
{
    RECORD *first = NULL;
    RECORD *remove = NULL;
    int records = 0;
    int position = 0;
    int i =0;
    char input = '\0';

    char search[50+1];
    int value;




    while(input!='k')
    {
        scanf("%c",&input);

        if(input=='n')
        {
            n(&first,&records);
        }

        if(input=='v')
        {
            v(first,records);
        }

        if(input=='p')
        {
            scanf("%d",&position);
            p(&first,&records,position);
        }

        if(input=='z')
        {
            scanf(" %[^\n]s",search);
            z(&first,&records,search);
        }

        if(input=='h')
        {
            scanf("%d",&value);
            h(first,records,value);
        }

        if(input=='a')
        {
            scanf(" %[^\n]s",search);
            a(first,records,search);
        }

    }

    // // dealokacia zaznamu pred ukoncenim // //
    if(first==NULL)
    {

    }
    else
    {
        for(i=0;i<records;i++)
        {
        remove=first;
        first=first->next;
        free(remove);
        }

    }

    return 0;
}

// V turingu funguje len po pridani medzery na 22. riadok, ktory tam podla zadania ma byt
