#include<stdio.h>
#include<stdlib.h>

typedef struct nod
{
    int cheie;
    struct nod *stanga;
    struct nod *dreapta;
    int inaltime;
}nod;

struct nod *radacina=NULL;

struct nod *inserare(int ch)
{
    struct nod *aux=(struct nod*)malloc(sizeof(struct nod));
    aux->cheie=ch;
    aux->dreapta=NULL;
    aux->stanga=NULL;
    aux->inaltime=1;
    return aux;
}

int maxim(int x,int y)
{
    if(x>y)
    return x;
    return y;
}

int inaltimea(struct nod *radacina)
{
    if(radacina)
    {
    int intaltime_stanga=inaltimea(radacina->stanga);
    int inaltime_dreapta=inaltimea(radacina->dreapta);
    return (1+(maxim(intaltime_stanga,inaltime_dreapta)));
    }
    return 0;
}

int factor_echilibru(struct nod *radacina)
{
    if(radacina)
    {
        int stang=inaltimea(radacina->stanga);
        int drept=inaltimea(radacina->dreapta);
        return stang-drept;
    }
    return 0;
}

struct nod *rot_stanga(struct nod *radacina)
{
    if(radacina)
    {
        struct nod *stang=radacina->stanga;
        radacina->stanga=stang->dreapta;
        stang->dreapta=radacina;
        return stang;
    }
    return radacina;
}

struct nod *rot_dreapta(struct nod *radacina)
{
    if(radacina)
    {
        struct nod *drept=radacina->dreapta;
        radacina->dreapta=drept->stanga;
        drept->stanga=radacina;
        return drept;
    }
    return radacina;
}

int avl_echilibrat=1;

struct nod *bst_avl(struct nod *n,int ch)
{
    if(n==NULL)
    return (inserare(ch));
    if(ch<n->cheie)
    n->stanga=bst_avl(n->stanga,ch);
    else if(ch>n->cheie)
    n->dreapta=bst_avl(n->dreapta,ch);
    else
    return n;
    if(factor_echilibru(n)==2 || factor_echilibru(n)==-2)
    {
        avl_echilibrat=0;
        printf("Arborele nu este echilibrat daca nu este rotit\n");
        exit(EXIT_FAILURE);
    }
    if(factor_echilibru(n)==2)
    {
        if(factor_echilibru(n->stanga)==1)
        n=rot_stanga(n);
        else
        {
            n->stanga=rot_dreapta(n->stanga);
            n=rot_stanga(n);
        }
    }
    if(factor_echilibru(n)==-2)
    {
        if(factor_echilibru(n->dreapta)==-1)
        n=rot_dreapta(n);
        else
        {
            n->dreapta=rot_stanga(n->dreapta);
            n=rot_dreapta(n);
        }
    }
    avl_echilibrat=1;
    return n;
}

void preordine(struct nod *n)
{
    if(n!=NULL)
    {
        printf("%d ",n->cheie);
        preordine(n->stanga);
        preordine(n->dreapta);
    }
}

int main()
{
    int ch;
    printf("Cheie: "); scanf("%d",&ch); radacina=bst_avl(radacina,ch);
    printf("Cheie: "); scanf("%d",&ch); radacina=bst_avl(radacina,ch);
    printf("Cheie: "); scanf("%d",&ch); radacina=bst_avl(radacina,ch);
    printf("Cheie: "); scanf("%d",&ch); radacina=bst_avl(radacina,ch);
    printf("Cheie: "); scanf("%d",&ch); radacina=bst_avl(radacina,ch);
    printf("Cheie: "); scanf("%d",&ch); radacina=bst_avl(radacina,ch);
    printf("Cheie: "); scanf("%d",&ch); radacina=bst_avl(radacina,ch);
    if(avl_echilibrat==1)
    printf("Arborele e echilibrat fara sa se faca rotatii\n");
    preordine(radacina);
    return 0;
}