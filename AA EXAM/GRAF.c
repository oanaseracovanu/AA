#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int mat_adj[20][20],nr_noduri,mat_ponderi[20][20],noduri[20],vizitate[20],mat_prim[20][20];

void initializare(int x)
{
    int i;
    for(i=0;i<x;i++)
    {
        mat_adj[i][i]=0;
        mat_ponderi[i][i]=0;
    }
}

void introducere_nod(int x,int i)
{
    noduri[i]=x;
}

void introducere_arc(int x,int y)
{
    int i=-1,j=-1,poz,pondere;
    for(poz=0;poz<nr_noduri;poz++)
    {
    if(noduri[poz]==x)
    i=poz;
    else
    if(noduri[poz]==y)
    j=poz;
    if(i!=-1 && j!=-1)
    {
        mat_adj[i][j]=1;
        mat_adj[j][i]=1;
    }
    }
    printf("Ponderea: ");
    scanf("%d",&pondere);
    mat_ponderi[i][j]=pondere;
    mat_ponderi[j][i]=pondere;
   
}

int cautare_nod(int x)
{
    int i,ok=0;
    for(i=0;i<nr_noduri;i++)
    if(noduri[i]==x)
    return 1;
    return 0;
}

void cautare_arc(int x,int y)
{
    int i=-1,j=-1,poz;
    for(poz=0;poz<nr_noduri;poz++)
    if(noduri[poz]==x)
    i=poz;
    else if (noduri[poz]==y)
    j=poz;
    if(i==-1 || j==-1)
    printf("Introduceti noduri care apartin grafului!\n");
    if(mat_adj[i][j]==1 && mat_adj[j][i]==1)
    printf("Arcul exista si are ponderea: %d",mat_ponderi[i][j]);
    else
    printf("Arcul nu exista!\n");
}

void prim()
{
    int i,j,i_min,j_min,min=32676,contor=0,suma=0;
    for(i=0;i<nr_noduri;i++)
    for(j=0;j<nr_noduri;j++)
    mat_prim[i][j]=0;
    while(contor<nr_noduri)
    {
    for(i=0;i<nr_noduri;i++)
    for(j=0;j<nr_noduri;j++)
    if((vizitate[i]==0 || vizitate[j]==0) && mat_prim[i][j]==0)
    if(mat_ponderi[i][j]<min && mat_ponderi[i][j])
    {
        min=mat_ponderi[i][j];
        i_min=i; 
        j_min=j;
    }
    if(min!=32676)
    {
        printf("\nArcul %d %d cu ponderea: %d\n", i_min, j_min, mat_ponderi[i_min][j_min]);
        mat_prim[i_min][j_min]=1;
        if(vizitate[i_min]==0)
        { 
        vizitate[i_min]=1; 
        contor++; 
        }
        if(vizitate[j_min]==0)
        { 
        vizitate[j_min]=1; 
        contor++; 
        }
        suma=suma+min;
        min=32676;
    }
    else contor=contor+2;
    }
    printf("Distanta minima este %d\n", suma);
}

void afisare()
{
    int i,j;
    printf("Nodurile grafului: \n");
    for(i=0;i<nr_noduri;i++)
    printf("%d ",noduri[i]);
    printf("\nMatricea de adiacenta: \n");
    for(i=0;i<nr_noduri;i++)
    {
    for(j=0;j<nr_noduri;j++)
    printf("%d ",mat_adj[i][j]);
    printf("\n");
    }
    printf("\nMatricea cu ponderi: \n");
    for(i=0;i<nr_noduri;i++)
    {
        for(j=0;j<nr_noduri;j++)
        printf("%d ",mat_ponderi[i][j]);
        printf("\n");
    }

}

void stergere(int x)
{
    int i,j,aux;
    for(i=0;i<nr_noduri;i++)
    if(noduri[i]==x)
    {
    j=i;
    break;
    }
    for(i=j+1;i<nr_noduri;i++)
    noduri[i-1]=noduri[i];
    for(i=j+1;i<nr_noduri;i++)
    for(aux=0;aux<nr_noduri;aux++)
    {
    mat_adj[i-1][aux]=mat_adj[i][aux];
    mat_ponderi[i-1][aux]=mat_ponderi[i][aux];
    }
    for(i=j+1;i<nr_noduri;i++)
    for(aux=0;aux<nr_noduri;aux++)
    {
        mat_adj[aux][i-1]=mat_adj[aux][i];
        mat_ponderi[aux][i-1]=mat_ponderi[aux][i];
    }
 
}

void stergere_arc(int x,int y)
{
    int i=-1,j=-1,poz;
    for(poz=0;poz<nr_noduri;poz++)
        if(noduri[poz]==x)
        {
            i=poz;
            printf("%d %d\n",noduri[poz],poz);
            break;
        }
        for(poz=0;poz<nr_noduri;poz++)
        if(noduri[poz]==y)
        j=poz;
        printf("%d %d\n",i,j);
        if(i==-1 || j==-1)
        printf("Introduceti noduri care apartin grafului!\n");
        else
        {
            if(mat_adj[i][j]==1 && mat_adj[j][i]==1)
            {
                printf("Arcul exista ");
                mat_adj[i][j]=-1;
                mat_adj[j][i]=-1;
                mat_ponderi[i][j]=-1;
                mat_ponderi[j][i]=-1;
            }
            else
            printf("Arcul nu exista\n");
        }
}

int main()
{
    int opt,nod,nod1,nod2,count,i,j;
    printf("Numarul total de noduri: ");
    scanf("%d",&nr_noduri);
    initializare(nr_noduri);
    do
    {
        printf("\n0.Iesire\n");
        printf("1.Introducere noduri\n");
        printf("2.Introducere arcuri\n");
        printf("3.Cautare nod\n");
        printf("4.Cautare arc\n");
        printf("5.Afisare\n");
        printf("6.Algoritmul lui prim\n");
        printf("7.Stergere nod\n");
        printf("8.Stergere arc\n");
        printf("Optiunea dumneavoastra: ");
        scanf("%d",&opt);
        switch(opt)
        {
            case 0:
            exit(0);
            break;
            case 1:
            for(i=0;i<nr_noduri;i++)
            {
                printf("Nodul de introdus: ");
                scanf("%d",&nod);
                introducere_nod(nod,i);
            }
            break;
            case 2:
            printf("Intre ce noduri doriti sa inserati arc? ");
            scanf("%d %d",&nod1,&nod2);
            introducere_arc(nod1,nod2);
            break;
            case 3:
            printf("Nodul pe care doriti sa il cautati: ");
            scanf("%d",&nod);
            if(cautare_nod(nod)==1) 
            printf("Nodul se afla in graf\n");
            else
            printf("Nodul nu se afla in graf\n");
            break;
            case 4:
            printf("Nodurile intre care doriti sa cautati arcul: ");
            scanf("%d %d",&nod1,&nod2);
            cautare_arc(nod1,nod2);
            break;
            case 5:
            afisare();
            break;
            case 6:
            prim();
            break;
            case 7:
            printf("Nodul pe care doriti sa il stergeti: ");
            scanf("%d",&nod);
            stergere(nod);
            nr_noduri--;
            break;
            case 8:
            printf("Nodurile intre care se afla arcul pe care doriti sa il eliminati: ");
            scanf("%d %d",&nod1,&nod2);
            stergere_arc(nod1,nod2);
            break;
        }
    } while (1);
    
    return 0;
}