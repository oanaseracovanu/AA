#include<stdio.h>
#include<stdlib.h>
#include<math.h> 

int noduri[100],nr_noduri=0,mat_adj[100][100],mat_ponderi[100][100],stergere[100];

void initializare(int x)
{
    int i,j;
    for(i=0;i<nr_noduri;i++)
    noduri[i]=0; //vectorul unde vor fi stocate nodurile, initializat cu 0
    for(i=0;i<x;i++)
    for(j=0;j<x;j++)
    {
    mat_adj[i][j]=-1;  //creare matrice de adiacenta si initializare cu -1
    mat_ponderi[i][j]=-1; //creare matrice ponderata si initializare cu -1
    }
}

void introducere_nod(int x,int i)
{
    noduri[i]=x; //introducere nod pe pozitie
}

int prima_cifra(int x)
{
    while(x>9) //daca nr e mai mic de 9 va da 0 
    x=x/10; //se imparte la 10 
    return x; //la final va ramane doar prima cifra
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
        if(x%2==0 && y%2!=0) //daca primul nod e par si al doilea impar
        mat_adj[i][j]=1; //introduce arc de la el (x) la y
        if(x%2!=0 && y%2==0) //daca primul e impar si al doilea par
        mat_adj[j][i]=1; //introduce arc de la y la x
    }
    }
    if(x%2==0 && y%2!=0)
    mat_ponderi[i][j]=abs(prima_cifra(noduri[i])-prima_cifra(noduri[j])); //ponderea este suma modulul diferentei dintre primele cifre ale nodurilor 
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

void stergere_nod(int x) //stergerea unui nod introdus de la tastatura
{
    int i,j,aux;
    for(i=0;i<nr_noduri;i++)
    if(noduri[i]==x) //daca am gasit nodul
    {
    j=i; //retinem pozitia 
    break;
    }
    for(i=j+1;i<nr_noduri;i++) //pornind de la nodul urmator pozitiei aflate
    noduri[i-1]=noduri[i]; //mutam totul cu o pozitie
    for(i=j+1;i<nr_noduri;i++)
    for(aux=0;aux<nr_noduri;aux++)
    {
    mat_adj[i-1][aux]=mat_adj[i][aux]; //la fel si pentru matrici
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
    k_min=i; //retinem pozitia minima
    for(j=i+1;j<nr_noduri;j++)
	{
	if(stergere[j]<stergere[k_min]) //daca gasim un element mai mic
	{
	k_min=j; //actualizam pozitia
	}
	}
    //interschimbare pentru a stoca elementul mai mic aflat
    x=stergere[i]; 
    stergere[i]=stergere[k_min];
    stergere[k_min]=x;
    }
    for(i=0;i<3;i++)
    for(j=0;j<nr_noduri;j++)
    {
    if(noduri[j]==stergere[i]) //daca am gasit unul din primele 3 noduri
    {
    stergere_nod(noduri[j]); //il stergem
    nr_noduri--; //actualizam nr total de noduri
    }
    }
}

int main(int argc, char *argv[]) //argumentele liniei de comanda
{
    int i,j;
    initializare(argc-1); //initializam vectorul de noduri si matricile
    for(i=1;i<argc;i++) //argc ne arata nr de noduri, fara prima pozitie deoarece aceea e denumirea fisierului
    {
    noduri[i-1]=atoi(argv[i]); //punem nodurile in vector
    introducere_nod(noduri[i-1],i-1); //introducem nodurile 
    nr_noduri++; //actualizam contorul numarului total de noduri
    }
    for(i=0;i<nr_noduri;i++)
    for(j=0;j<nr_noduri;j++)
    introducere_arc(noduri[i],noduri[j]); //introducem arce intre toate nodurile pare si impare
    afisare(); //afisam 
    for(i=0;i<nr_noduri;i++)
    stergere[i]=noduri[i]; //initializam vectorul auxiliar in care se vor retine nodurile pt a putea afla primele 3 cele mai mici
    sortare_noduri(); //facem sortarea si stergerea in intermediul acestei functii
    afisare(); //afisam actualizarile 
    return 0;
}