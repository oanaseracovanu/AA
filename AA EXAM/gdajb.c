#include<stdio.h>
#include<stdlib.h>
#include<math.h> 

int mat_adj[100][100],nr_noduri=0,mat_ponderi[100][100],noduri[100],stergere[100];

void initializare(int x)
{
    int i,j;
    for(i=0;i<nr_noduri;i++)
    noduri[i]=0;
    for(i=0;i<x;i++)
    for(j=0;j<x;j++)
    {
    mat_adj[i][j]=-1;  //creare matrice de adiacenta
    mat_ponderi[i][j]=-1; //creare matrice ponderata
    }
}

void introducere_nod(int x,int i)
{
    noduri[i]=x; //introducere nod pe pozitie
}

int prima_cifra(int x)
{
    while(x>9)
    x=x/10;
    return x;
}

void introducere_arc(int x,int y)
{
    int i=-1,j=-1,poz,pondere;
    for(poz=0;poz<nr_noduri;poz++)
    {
    if(noduri[poz]==x)
    i=poz; //retinere pozitie
    else
    if(noduri[poz]==y)
    j=poz; //retinere pozitie
    if(i!=-1 && j!=-1) //daca nodurile au fost gasite
    {
        if(x%2==0 && y%2!=0) //daca primul e par si al doilea impar
        mat_adj[i][j]=1; //introduce arc de la el (x) la y
        if(x%2!=0 && y%2==0) //daca primul e mai mare
        mat_adj[j][i]=1; //introduce arc de la y la x
    }
    }
    if(x%2==0 && y%2!=0)
    mat_ponderi[i][j]=abs(prima_cifra(noduri[i])-prima_cifra(noduri[j])); //ponderea este suma primelor cifre
    if(x%2!=0 && y%2==0)
    mat_ponderi[j][i]=abs(prima_cifra(noduri[i])-prima_cifra(noduri[j])); 

}

void afisare() //afisare noduri si matrici
{
    int i,j;
    printf("Matricea de adiacenta: \n");
    printf("    %d  ",noduri[0]);
    for(i=1;i<nr_noduri;i++)
    printf(" %d  ",noduri[i]);
    printf("\n");
    for(i=0;i<nr_noduri;i++)
    {
    printf("%  d ",noduri[i]);
    for(j=0;j<nr_noduri;j++)
    printf("%   d  ",mat_adj[i][j]);
    printf("\n");
    }
    printf("\nMatricea cu ponderi: \n");
    printf("    %d   ",noduri[0]);
    for(i=1;i<nr_noduri;i++)
    printf("%d  ",noduri[i]);
    printf("\n");
    for(i=0;i<nr_noduri;i++)
    {
        printf("%   d ",noduri[i]);
        for(j=0;j<nr_noduri;j++)
        printf("%   d  ",mat_ponderi[i][j]);
        printf("\n");
    }

}

void stergere_noduri(int x) //stergerea unui nod introdus de la tastatura
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

void sortare_noduri()
{
    int i,j,k_min,x;
    for(i=0;i<nr_noduri;i++)
    {
    k_min=i;
    for(j=i+1;j<nr_noduri;j++)
	{
	if(stergere[j]<stergere[k_min])
	{
	k_min=j;
	}
	}
    x=stergere[i];
    stergere[i]=stergere[k_min];
    stergere[k_min]=x;
    }
    for(i=0;i<3;i++)
    for(j=0;j<nr_noduri;j++)
    {
    if(noduri[j]==stergere[i])
    {
    stergere_noduri(noduri[j]);
    nr_noduri--;
    }
    }
}

int main()
{
    int opt,nod,nod1,nod2,count,i,j;
    printf("Nr noduri: ");
    scanf("%d ",&nr_noduri);
    initializare(nr_noduri);
    for(i=0;i<nr_noduri;i++)
    {
    printf("Nod: ");
    scanf("%d",&nod);
    introducere_nod(nod,i);
    }
    for(i=0;i<nr_noduri;i++)
    for(j=0;j<nr_noduri;j++)
    introducere_arc(noduri[i],noduri[j]);
    afisare();
    for(i=0;i<nr_noduri;i++)
    stergere[i]=noduri[i];
    sortare_noduri();
    afisare();
    return 0;
}