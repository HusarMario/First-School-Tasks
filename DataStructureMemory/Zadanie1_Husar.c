#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


/* V komentároch pouzivam nazvy prazdny/volny blok a uvolneny blok
    prazdny/volny blok predstavuje pamat ktora este nebola nikdy predtym alokovana a uvloneny blok pamat ktora bola uvolnena funkciou memory_free */

void *empty;

void memory_init(void *ptr,unsigned int size)
{
    /*printf("%p\n",ptr);*/     /* Testovacia hodnota pre zistenie lokacie pamate */

    *(int*)ptr = 12;        /* Pouzivane na najdenie prazdneho bloku */
    ptr=ptr+4;
    *(int*)ptr = size-12;   /* Pouzivane na zistenie velkosti prazdneho bloku */
    ptr=ptr+4;
    *(int*)ptr = 0;         /* Pouzivane na najdenie prveho uvolneneho bloku */

    ptr=ptr-8;
    empty=ptr;
}

void *memory_alloc(unsigned int size)
{
    void *back;             /* Pouzivane na vratenie sa do hlavicky */
    void *out;              /* Pouzivane na vypustenie smernika z funkcie */

    int i;
    void *search;
    void *curr;
    void *prev;
    void *last;
    int b_last=0;
    int counter;

    int option1=0;          /* Zapisovanie udajov v pripade ze je hlavny blok zaplneny */
    int b_opt1=0;
    void *opt1;
    void *p_opt1;
    int option2=0;
    int b_opt2=0;
    void *opt2;
    void *p_opt2;

    opt1=empty;
    opt2=empty;
    p_opt1=empty;
    p_opt2=empty;

    if(size<=4)             /* Velkosti od 1-4 budu automaticky zmenene na velkost 4 --> pre lepsie hladanie prazdnych blokov */
        size=4;

    search=empty+8;

    if(*(int*)search!=0)        /* Overenie ci existuje nejaky uvolneny blok -- ak ano zacne prehladavat vsetky volne bloky */
    {
        curr=empty+*(int*)search;
        counter=*(int*)search;

        *(int*)curr=~*(int*)curr;

        if(*(int*)curr>size+8)
        {
            option1=*(int*)curr;
            b_opt1=1;
            opt1=curr;
        }

        if((*(int*)curr<size+8)&&(*(int*)curr>size))
        {
            option2=*(int*)curr;
            b_opt2=1;
            opt2=curr;
        }


        if(size==*(int*)curr)   /* Overenie ci uvolneny blok ma presne rovnaku velkost ako je potrebna -- ak ano obsadi ho */
        {
            curr=curr+4;
            *(int*)search=*(int*)search+*(int*)curr;

            if(*(int*)empty==*(int*)search) /* Ak uvolneny blok bol len jeden a ten sa zaplni, pocet uvolnenych blokov vynuluje */
            {
                *(int*)search=0;
            }

            *(char*)curr='\0';
            curr++;
            *(char*)curr='\0';
            curr++;
            *(char*)curr='\0';
            curr++;
            *(char*)curr='\0';
            curr++;

            curr=curr-4;

            for(i=0;i<size;i++)
            {
                *(char*)curr='#';
                curr++;
            }

            curr=curr-size-4;
            out=curr;
            out=out+4;

            return out;
        }
        *(int*)curr=~*(int*)curr;

        prev=curr;
        curr=curr+4;
        last=curr;
        b_last=1;
        counter=counter+*(int*)curr;
        curr=curr+*(int*)curr-4;


        while(counter!=*(int*)empty)    /* Overovanie vsetkych ostatnych blokov rovnako ako pri prvom (prvy je vytvoreny zvlast pre vynimocne pripady) */
        {
            *(int*)curr=~*(int*)curr;

            if(*(int*)curr>size+8)
            {
                if(b_opt1==0)
                {
                    option1=*(int*)curr;
                    b_opt1=1;
                    opt1=curr;
                    p_opt1=prev;
                }
                else
                {
                    if(*(int*)curr<option1)
                    {
                        option1=*(int*)curr;
                        opt1=curr;
                        p_opt1=prev;
                    }
                }
            }

            if((*(int*)curr<size+8)&&(*(int*)curr>size))
            {
                if(b_opt2==0)
                {
                    option2=*(int*)curr;
                    b_opt2=1;
                    opt2=curr;
                    p_opt2=prev;
                }
                else
                {
                    if(*(int*)curr<option2)
                    {
                        option2=*(int*)curr;
                        opt2=curr;
                        p_opt2=prev;
                    }
                }
            }



            if(size==*(int*)curr)
            {
                prev=prev+4;
                curr=curr+4;

                *(int*)prev=*(int*)prev+*(int*)curr;

                *(char*)curr='\0';
                curr++;
                *(char*)curr='\0';
                curr++;
                *(char*)curr='\0';
                curr++;
                *(char*)curr='\0';
                curr++;

                curr=curr-4;

                for(i=0;i<size;i++)
                {
                    *(char*)curr='#';
                    curr++;
                }

                curr=curr-size-4;
                out=curr;
                out=out+4;

                return out;
            }

            *(int*)curr=~*(int*)curr;

            prev=curr;
            curr=curr+4;
            counter=counter+*(int*)curr;
            last=curr;
            b_last=1;
            curr=curr+*(int*)curr-4;
        }
    }


    empty=empty+4;
    if((size+4)>*(int*)empty)           /* Overenie ci volny blok je dostatocne velky */
    {
        empty=empty-4;
    }
    else                                /* Vkladanie bloku na zaciatok volnej pamate */
    {
        empty=empty-4;

        back=empty;
        empty=empty+*(int*)empty;

        *(int*)empty=size;
        empty=empty+4;

        for(i=0;i<size;i++)
        {
            *(char*)empty='#';
            empty++;
        }
        empty=empty-size-4;
        out=empty;

        empty=empty-*(int*)back;
        *(int*)empty=*(int*)empty+4+size;
        empty=empty+4;
        *(int*)empty=*(int*)empty-4-size;
        empty=empty-4;

        if(b_last==1)
            *(int*)last=*(int*)last+size+4;

        out=out+4;

        return out;
    }


    if(b_opt1==1)           /* Vkladanie bloku na miesto, kde po obsadeni zostane dostatocna velkost pre dalsi blok(aspon 8) */
    {
        curr=opt1;
        out=opt1;

        if(p_opt1==empty)
        {
            p_opt1=p_opt1+8;
            *(int*)p_opt1=*(int*)p_opt1+size+4;
        }
        else
        {
            p_opt1=p_opt1+4;
            *(int*)p_opt1=*(int*)p_opt1+size+4;
        }

        *(int*)opt1=~*(int*)opt1;

        curr=curr+4+size;

        *(int*)curr=*(int*)opt1-size-4;
        *(int*)curr=~*(int*)curr;

        *(int*)opt1=size;

        curr=curr+4;
        opt1=opt1+4;

        *(int*)curr=*(int*)opt1-size-4;

        *(char*)opt1='\0';
        opt1++;
        *(char*)opt1='\0';
        opt1++;
        *(char*)opt1='\0';
        opt1++;
        *(char*)opt1='\0';
        opt1++;

        opt1=opt1-4;

        for(i=0;i<size;i++)
            {
                *(char*)opt1='#';
                opt1++;
            }


        out=out+4;
        return out;
    }

    if(b_opt2==1)           /* Vkladanie bloku na miesto s vacsim priestorom ako je potrebne - vznika fragmentacia */
    {
        curr=opt2;
        out=opt2;

        curr=curr+4;

        if(p_opt2==empty)
        {
            p_opt2=p_opt2+8;
            *(int*)p_opt2=*(int*)p_opt2+*(int*)curr;
        }
        else
        {
            p_opt2=p_opt2+4;
            *(int*)p_opt2=*(int*)p_opt2+*(int*)curr;
        }

        *(char*)curr='\0';
        curr++;
        *(char*)curr='\0';
        curr++;
        *(char*)curr='\0';
        curr++;
        *(char*)curr='\0';
        curr++;

        *(int*)opt2=~*(int*)opt2;

        opt2=opt2+4;
        for(i=0;i<size;i++)
            {
                *(char*)opt2='#';
                opt2++;
            }

        out=out+4;
        return out;
    }

    return NULL;
}

int memory_maintance(void *newest)      /* Pomocna funkcia na prepajanie uvlonenych blokov */
{
    void *search;
    int counter;

    void *first;
    void *second;

    int first_count=0;
    int second_count=0;

    void *header;

    search=empty;
    search=search+8;

    if(*(int*)search==0)            /* Spravovanie uvlonenych blokov v pripade ze neexistuje uvolneny blok */
    {
        search=search+4;
        counter=12;

        while(search!=newest)
        {
            counter=counter+*(int*)search+4;
            search=search+*(int*)search+4;
        }

        empty=empty+8;
        *(int*)empty=counter;
        empty=empty-8;

        search=search+4;
        *(int*)search=*(int*)empty-counter;

        return 0;
    }

    search=search+4;
    counter=12;

    while(search!=newest)
    {
        if(*(int*)search>0)
        {
            counter=counter+*(int*)search+4;
            search=search+*(int*)search+4;
        }
        else if(*(int*)search<0)
        {
            counter=counter+~*(int*)search+4;
            search=search+~*(int*)search+4;
        }

    }

    header=empty;
    header=header+8;

    if(counter<*(int*)header)   /* Spravovanie uvlonenych blokov ak najnovsi blok je pred prvym uvlonenym blokom */
    {
        search=search+4;
        *(int*)search=*(int*)header-counter;
        *(int*)header=counter;

        return 0;
    }


    first=empty;
    second=empty;

    first=first+8;
    first_count=*(int*)first;
    first=first-8;

    second=empty+first_count+4;
    second_count=first_count+*(int*)second;
    second=second-4;

    if ((counter>first_count)&&(counter<second_count))  /* Spravovanie uvlonenych blokov ak najnovsi blok medzi dvoma uvolnenymi blokmi */
    {
        first=first+first_count+4;
        *(int*)first=counter-first_count;

        search=search+4;
        *(int*)search=second_count-counter;

        return 0;
    }

    while(second_count!=*(int*)empty)    /* Spravovanie uvlonenych blokov ak najnovsi blok je poslednym blokom */
    {
        first=empty+first_count;
        first=first+4;
        first_count=first_count+*(int*)first;
        first=first-4;

        second=empty+second_count;
        second=second+4;
        second_count=second_count+*(int*)second;
        second=second-4;

        if((counter>first_count)&&(counter<second_count))
        {
            first=empty+first_count+4;
            *(int*)first=counter-first_count;

            search=search+4;
            *(int*)search=second_count-counter;

            break;
        }
    }

    return 0;
}

int memory_connection()                 /* Pomocna funkcia na spajanie vedlajsich uvlonenych blokov */
{
    void *search;
    void *second;

    int counter=0;
    int last=0;

    int size;
    int next;
    int i;

    search=empty;
    search=search+8;
    counter=*(int*)search;

    if(*(int*)search==0)            /* Overenie ci existuje uvolneny blok */
    {
        return 0;
    }

    search=search-8;
    search=search+counter;

    while(counter!=*(int*)empty)       /* Hladanie susednych blokov */
    {
        size=0;
        next=0;

        *(int*)search=~*(int*)search;
        size=*(int*)search+4;
        *(int*)search=~*(int*)search;

        search=search+4;
        next=*(int*)search;
        search=search-4;



        if(size==next)              /* Najdenie zhody */
        {
            if(counter+next==*(int*)empty)  /* Ak spajam posledny blok presunie sa na specialny samostatny loop */
            {
                last=1;
                break;
            }

            second=search;
            second=second+next;

            *(int*)search=~*(int*)search;
            *(int*)second=~*(int*)second;
            *(int*)search=*(int*)search+*(int*)second+4;
            *(int*)second=~*(int*)second;
            *(int*)search=~*(int*)search;

            *(char*)second='\0';
            second++;
            *(char*)second='\0';
            second++;
            *(char*)second='\0';
            second++;
            *(char*)second='\0';
            second++;

            search=search+4;
            *(int*)search=*(int*)search+*(int*)second;
            search=search-4;

            *(char*)second='\0';
            second++;
            *(char*)second='\0';
            second++;
            *(char*)second='\0';
            second++;
            *(char*)second='\0';
            second++;
        }

        else
        {
            second=search;
            second=second+4;
            counter=counter+*(int*)second;
            search=search+*(int*)second;
        }
    }

    if(last==1)     /* Spajanie koncoveho bloku */
    {
        empty=empty+8;
        if(counter==*(int*)empty)
        {
            *(int*)empty=0;
        }
        empty=empty-8;

        for(i=0;i<8;i++)
        {
            *(char*)search='\0';
            search++;
        }

        *(int*)empty=*(int*)empty-size;
        empty=empty+4;
        *(int*)empty=*(int*)empty+size;
        empty=empty-4;

        last=0;
    }


    return 0;
}

int memory_free(void *valid_ptr)
{
    valid_ptr=valid_ptr-4;
    int size=*(int*)valid_ptr;
    valid_ptr=valid_ptr+4;

    int i;

    for(i=0;i<size;i++)
    {
        *(char*)valid_ptr='\0';
        valid_ptr++;
    }

    valid_ptr=valid_ptr-size-4;
    *(int*)valid_ptr=~(*(int*)valid_ptr);       /* Velkost bloku ostane zachovana ale prevrati sa */

    memory_maintance(valid_ptr);

    memory_connection();

    return 1;
}

int memory_check(void *ptr)
{
    ptr=ptr-4;

    if(*(int*)ptr>0)          /* Hodnoty su vzdy zaporne alebo kladne .. kladne==obsadeny blok .. zaporne==uvolneny blok */
    return 1;

    else
    return 0;
}


int main()
{

    return 0;
}



