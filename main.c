#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

struct node
{
    int sayi;
    int kac;
    char word[20];
    struct node *next;
};

struct node *head, *temp, *q, *tempq;

int kelimeAra(char *s)
{
    int x = 0;
    struct node *ara = head;

    while(ara!=NULL)
    {
        if(strcmp(ara->word,s)==0)
            x=1;
        ara=ara->next;
    }
    return x;
}

int kelimeSay(char *s)
{
    int adet = 0;
    char str2[20];
    FILE *fp = fopen("kelimeler.txt", "r+");

    if(fp == NULL)
    {
        printf("Dosya acilamadi.");
        return 1;
    }
    while(fscanf(fp,"%s ",str2)!=EOF)
    {
        if(strcmp(str2,s)==0)
            adet++;
    }

    fclose(fp);
    return adet;
}

void basaEkle(char *s, int n)
{
    struct node *tmp = (struct node*)malloc(sizeof(struct node));
    strcpy(tmp->word,s);
    tmp->sayi = n;
    tmp->next = head;
    tmp->kac = 0;
    head = tmp; //baştaki eleman tmp ye eşit
}
int k = 0;
void arayaEkle(char *s, int n)
{
    k++;
    struct node *tmp3 = (struct node*)malloc(sizeof(struct node));
    strcpy(tmp3->word,s);
    tmp3->sayi = n;
    tmp3->kac = k;
    q = head;

    while(q->next->sayi >= n)
    {
        q = q->next;
    }

    struct node *tmp4 = (struct node*)malloc(sizeof(struct node));
    tmp4 = q->next;
    q->next = tmp3;
    tmp3->next = tmp4;
}

void sonaEkle(char *s)
{
    struct node *tmp2 = (struct node*)malloc(sizeof(struct node));
    strcpy(tmp2->word,s);
    tmp2->sayi = 1;
    tmp2->next = NULL;
    tmp2->kac = 9;
    if(head==NULL)
    {
        head = tmp2;
    }
    else
    {
        temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = tmp2;
    }
}
int no = 1;
char ssm[10] = "buControl";

void listele()
{
    no++;
    struct node *liste = head;
    int i=1;
    while(liste!=NULL)
    {
        if(liste->kac < 1000)
        {
            if(strcmp(liste->word,ssm)!=0)
            {
                printf("%d: %d adet, kelime: %s -- kacinci sirada eklendi: %d \n",i,liste->sayi,liste->word, liste->kac);
                i++;
            }
        }
        liste = liste->next;
    }
}

void myList()
{
    struct node *list = head;
    struct node *onceki = NULL;
    struct node *sonraki = NULL;

    while(list->next->kac < 1000)
    {
        list = list->next;
    }

    onceki = list;
    sonraki = list->next->next;
    free(list->next);
    onceki->next = sonraki;

    struct node *listx = head;
    struct node *oncekix = NULL;
    struct node *sonrakix = NULL;

    while(strcmp(listx->next->word,ssm)!=0)
    {
        listx = listx->next;
    }

    oncekix = listx;
    sonrakix = listx->next->next;
    free(listx->next);
    oncekix->next = sonrakix;
}

void listMyList()
{
    struct node *myList = head;
    int i=1;
    while(myList!=NULL)
    {
        printf("%d. %s: %d\n",i,myList->word,myList->sayi);
        i++;
        myList = myList->next;
    }
}

int main()
{
    FILE *dosya = fopen("kelimeler.txt", "r+");

    if(dosya == NULL)
    {
        printf("Dosya acilamadi.");
        return 1;
    }

    temp = (struct node*)malloc(sizeof(struct node));
    temp->next = NULL;
    head = temp;
    char str[20];
    int count  = 0;

    while(fscanf(dosya,"%s ",str)!=EOF)//metinin sonuna kadar gider
    {
        if(count==0)
        {
            head->sayi = kelimeSay(str);
            basaEkle(str,head->sayi);
            count++;
            sonaEkle(ssm);
        }
        else
        {
            if(kelimeAra(str)==1)
            {
                //printf("esit\n");
            }
            else
            {
                if(kelimeSay(str)==1)
                {
                    sonaEkle(str);

                }
                else if(kelimeSay(str) >= head->sayi)
                {
                    int n = kelimeSay(str);
                    basaEkle(str,n);
                }
                else
                {
                    int m = kelimeSay(str);
                    arayaEkle(str,m);
                }
            }
        }
    }

    myList();

    printf("\nListe:\n\n");
    listMyList();

    fclose(dosya);
    _getch();
    free(malloc);
    return 0;
}
