//nu,raspunsul nu este corect, aceea este parcurgerea in inordine

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct nod
{
    int cheie; //nodul de inserat
    struct nod *stanga; //pointer spre fiu stanga
    struct nod *dreapta; //pointer spre fiu dreapta
    int inaltime; //inaltimea
}nod;

nod *radacina;
int avl_echilibrat=1,contor=0,vector_sterg[20];

nod *initializare(nod *radacina)
{
    if(radacina!=NULL)
    free(radacina);
    radacina=NULL;
    return radacina;
}

int maxim(int x,int y)
{
    if(x>y)
    return x;
    return y;
}

int inalt(nod *n) //inaltime
{
    if(n!=NULL)
    {
        int inaltime_stanga=inalt(n->stanga);
        int inaltime_dreapta=inalt(n->dreapta);
        return(1+maxim(inaltime_stanga,inaltime_dreapta)); 
    }
    return -1;
}

int factor_echilibru(nod *n)
{
    if(n!=NULL)
    {
        int st=inalt(n->stanga); //inaltimea din stanga
        int dr=inalt(n->dreapta); //inaltimea din dreapta
        int echilibrat=st-dr; //factorul= diferenta dintre inaltimi
        if(echilibrat==0||echilibrat==1) //daca factorul este 0 (echilibrat perfect) sau 1 arborele este echilibrat
        return 1;
        else if(echilibrat>=2)
        return -5;
    }
    return -5;
}

nod *inserare(nod *n,int ch)
{
    if(n==NULL) 
    {
        nod *nd;
        nd=(nod*)malloc(sizeof(nod)); 
        if(nd==NULL)
        {
            printf("Eroare la alocarea noului nod\n");
            exit(EXIT_FAILURE);
        }
        nd->cheie=ch; 
        nd->dreapta=NULL; 
        nd->stanga=NULL;
        nd->inaltime=1; 
        return nd;
    }
    if(n!=NULL)
    {
        if(ch<n->cheie) //cheia=radacina < cheia nodului 
        n->stanga=inserare(n->stanga,ch); //nodul se insereaza in stanga
        else
        {
            if(ch>n->cheie) //radacina > cheia nodului
            n->dreapta=inserare(n->dreapta,ch); //nodul este inserat in dreapta
            else
            return n; 
        } 
    }
    if(n!=NULL && n->stanga!=NULL && n->dreapta!=NULL) //daca exista elemente atat in stanga cat si in dreapta nodului 
    n->inaltime=maxim(n->stanga->inaltime,n->dreapta->inaltime)+1; //intaltimea= maximul dintre inaltimile din ambele parti +1 (nodul)
    else
    {
        if(n!=NULL && n->stanga==NULL && n->dreapta!=NULL) //daca avem noduri doar in partea dreapta
        n->inaltime=maxim(0,n->dreapta->inaltime)+1; //inaltimea= inaltimea din dreapta +1
        else
        {
            if(n!=NULL && n->stanga!=NULL && n->dreapta==NULL) //noduri doar in partea stanga
            n->inaltime=maxim(n->stanga->inaltime,0)+1; //inaltimea= inaltimea din stanga +1
            else
            {
                if(n!=NULL && n->stanga==NULL && n->dreapta==NULL)
                n->inaltime=1; //daca nu sunt noduri nici in stanga nici in dreapta => inaltimea=1 (nodul)
            
            }      
        }
        
    }
    return n; //intoarcem datele nodului 
}

nod *predecesor(nod *n) //returneaza cel mai mare nod din subarborele stang
{
    nod *st=n;
    while(st!=NULL && st->dreapta!=NULL)
    st=st->dreapta;
    return st;
}

nod *succesor(nod *n) //returneaza cel mai mic nod din subarborele drept
{
    nod *dr=n;
    while(dr!=NULL && dr->stanga!=NULL)
    dr=dr->stanga;
    return dr;
}

nod *stergere(int nr,nod *n)
{
    if(n==NULL)
    return NULL; //nu avem ce sa stergem!
    if(n->cheie>nr)
    n->stanga=stergere(nr,n->stanga);
    else if(n->cheie<nr)
    n->dreapta=stergere(nr,n->dreapta);
    else
    {
        if(n->stanga==NULL)
        {
            n=n->dreapta;
            return n;
        }
        else if(n->dreapta==NULL)
        {
            n=n->stanga;
            return n;
        }
        if(n->stanga!=NULL)
        {
            n->cheie=predecesor(n->stanga)->cheie;
            n->stanga=stergere(predecesor(n->stanga)->cheie,n->stanga);
        }
        else
        {
            if(n->dreapta!=NULL)
            {
                n->cheie=succesor(n->dreapta)->cheie;
                n->dreapta=stergere(succesor(n->dreapta)->cheie,n->dreapta);
            }
        } 
    } 
    return n;
}

void inordine(nod *radacina)
{
    if(radacina!=NULL)
    {
    inordine(radacina->stanga); //stanga
    if(radacina->cheie%2!=0) //verificam daca numarul este impar
    {
        vector_sterg[contor]=radacina->cheie; //retinem valorile in vector pentru a fi sterse ulterior
        contor++;
    }
    printf("%d ", radacina->cheie);        
    inordine(radacina->dreapta); //dreapta
    }
}

void preordine(nod *radacina)
{
    if(radacina!=NULL)
    {
        printf("%d ",radacina->cheie); //radacina
        preordine(radacina->stanga); //stanga
        preordine(radacina->dreapta); //dreapta
    }
}

void verificare(nod *radacina)
{
    if(radacina!=NULL)
    {
        if(abs(factor_echilibru(radacina))>=2) //daca factorul de echilibru este >=2 sau <=-2
        {
            avl_echilibrat=0; //arborele nu este echilibrat
            return;
        }
    }
    verificare(radacina->stanga);
    verificare(radacina->dreapta);
}

int main()
{
    radacina=initializare(radacina);
    radacina=inserare(radacina,79);
    radacina=inserare(radacina,21);
    radacina=inserare(radacina,1);
    radacina=inserare(radacina,14);
    radacina=inserare(radacina,49);
    radacina=inserare(radacina,57);
    radacina=inserare(radacina,84);
    radacina=inserare(radacina,3);
    radacina=inserare(radacina,98);
    radacina=inserare(radacina,63);
    printf("Inordine inainte de stergerea numerelor impare: ");
    inordine(radacina);
    printf("\n");
    for(int i=0;i<contor;i++)
    radacina=stergere(vector_sterg[i],radacina); //stergem valorile impare stocate in vector
    printf("Dupa stergerea numerelor impare: ");
    preordine(radacina);
    printf("\n");
    if(avl_echilibrat==1)
    printf("Arborele e echilibrat AVL dupa stergere\n");
    else
    printf("Dezechilibrat dupa stergere\n");
    return 0;
}