#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct node /* základné definovanie štruktury */
{
    int height;
    int data;
    struct node *left;
    struct node *right;
};

void create_node(struct node **node, int input) /* vytvorenie jedneho dielu */
{
    struct node *create = (struct node*)malloc(sizeof(struct node));

    create->data = input;
    create->left = NULL;
    create->right = NULL;

    *node=create;
}

void insert_height(struct node **curr)  /* vlozenie vysky do struktury */
{
        struct node *search;
        struct node *next;
        int height = 0;
        int lheight = 0;
        int rheight = 0;

        search=*curr;

        if(search->left==NULL)
        {

        }
        else
        {
           next=search->left;
           lheight = next->height+1;
        }

        if(search->right==NULL)
        {

        }
        else
        {
           next=search->right;
           rheight = next->height+1;
        }

        if(lheight>rheight)     /* vyber ktora cesta je najdlhsia */
            height=lheight;
        else
            height=rheight;

        search->height=height;
}

int check_height(struct node **curr)    /* vypocet rozdielu dlzok - potreba vyvazovania*/
{
        struct node *search;
        struct node *next;
        int height = 0;
        int lheight = 0;
        int rheight = 0;

        search=*curr;

        if(search->left==NULL)
        {

        }
        else
        {
           next=search->left;
           lheight = next->height+1;
        }

        if(search->right==NULL)
        {

        }
        else
        {
           next=search->right;
           rheight = next->height+1;
        }

        height=lheight-rheight;
        return height;
}

void right_rotation(struct node **curr) /*rotacia vpravo*/
{
    struct node *x;
    struct node *y;
    struct node *z;

    x=*curr;
    y=x->left;
    z=y->right;

    y->right = x;
    x->left = z;

    insert_height(&x);
    insert_height(&y);

    *curr=y;
}

void left_rotation(struct node **curr)  /*rotacia vlavo*/
{
    struct node *x;
    struct node *y;
    struct node *z;

    x=*curr;
    y=x->right;
    z=y->left;

    y->left = x;
    x->right = z;

    insert_height(&x);
    insert_height(&y);

    *curr=y;
}

void insert(struct node **curr, int input)  /* vkladanie novej polozky */
{
    struct node *search;
    struct node *prev;
    int height = 0;

    if (*curr == NULL)     /* ak najde koncove miesto prida polozku */
    {
        create_node(&(*curr),input);
    }

    else                /* hladanie vhodneho miesta */
    {
        search=*curr;
        prev=*curr;

        if(input<search->data)
        {
            search=search->left;
            insert(&search,input);
            prev->left=search;
        }

        else if(input>search->data)
        {
            search=search->right;
            insert(&search,input);
            prev->right=search;
        }

        else if(input==search->data)    /*dupilkaty*/
        {
            return;
        }
    }

    search=*curr;

    insert_height(&(*curr));            /* po vlozeni vlozi prislusnu vysku */
    height = check_height(&(*curr));    /* a zisti ci je potrebne vyvazovat */

    if (height > 1)                     /* 4 moznosti pri ktorych treba vyvazovat ==> left-left,right-right,left-right,right-left */
    {
        if(input < search->left->data)
        {
            right_rotation(&(*curr));
        }
        else if(input > search->left->data)
        {
            left_rotation(&search->left);
            right_rotation(&(*curr));
        }
    }

    if (height<-1)
    {
        if(input > search->right->data)
        {
            left_rotation(&(*curr));
        }
        else if(input < search->right->data)
        {
            right_rotation(&search->right);
            left_rotation(&(*curr));
        }
    }


}

void search(struct node *curr, int input) /*hladanie polozky*/
{
    struct node *search;
    search=curr;

    while(1)
    {
        if(search==NULL)
        {
            printf("%d v strome neexistuje\n",input);
            break;
        }

        if(search->data==input)
        {
            printf("%d v strome existuje\n",input);
            break;
        }

        else if(input<search->data)
        {
            search=search->left;
        }

        else if(input>search->data)
        {
            search=search->right;
        }

    }

}


int main()
{

    return 0;
}
