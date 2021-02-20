#include <stdio.h>
#include <stdlib.h>
#define n 100

typedef struct nod
{
	int info;
	int pondere;
	struct nod* urm;
}nod;

nod *lista_adiacenta[n], *prim[n];
int vizitat[n],minim,contor=0,cost_minim=0,cost_total=0;

void initializare_graf()
{
	int i;
	struct nod *nd,*aux;
	for(i=0;i<n;i++)
	{
	if(lista_adiacenta[i]!=NULL)
	{
	nd=lista_adiacenta[i]->urm;
	free(lista_adiacenta[i]);
	while(nd!=NULL)
	{
	aux=nd;
	nd=nd->urm;
	free(aux);
	}
	}
    lista_adiacenta[i] = NULL;
	}
}

void initializare_arbore()
{
	int i;
	struct nod *arb,*aux;
	for(i=0;i<n;i++)
	{
	if(prim[i]!=NULL)
	{
	arb=prim[i]->urm;
	free(prim[i]);
	while(arb!=NULL)
	{
	aux=arb;
	arb=arb->urm;
	free(aux);
	}
	}
	prim[i] = NULL;
	}
}

int graf_plin()
{
	int i,contor_noduri=0,contor_arce=0;
	struct nod *nd;
	for(i=0;i<n;i++)
	{
	if(lista_adiacenta[i]!=NULL)
	{
	contor_noduri++;
	}
	}
	if(contor_noduri<n) 
    return 0;
	for(i=0;i<N;i++)
	{
	if(lista_adiacenta[i]!=NULL)
	{
	nd=lista_adiacenta[i]->urm;
	while(nd!=NULL)
	{
	contor_arce++;
	nd=nd->urm;
	}
	}
	}
	if(contor_arce<(n-1)*n) 
    return 0;
	else 
    return 1;
}

void inserare_nod(int nod_)
{
	int ok=0;
	nod *nd;
	if(graf_plin()==0)
	{
	if(lista_adiacenta[nod_]==NULL)
	{
	ok=1;
	nd=(nod*)malloc(sizeof(nod));
	if(nd==NULL)
	{
	printf("Eroare la alocarea memoriei pentru nod!\n");
	exit(EXIT_FAILURE);
	}
	nd->info=nod_;
	nd->pondere=0;
	nd->urm=NULL;
	lista_adiacenta[nod_]=nd;
	contor++;
	printf("Inserarea nodului %d a fost efectuata!\n", nod_);
	}
	}
	if(ok==0) 
    printf("Inserarea nu a putut fi efectuata!\n");
}

void inserare_arc(int nod1,int nod2,int pond)
{
	int i,ok=0;
	struct nod *nd,*anterior,*nod_;
	if(graf_plin()==0)
	{
	for(i=0;i<n;i++)
	{
	if(lista_adiacenta[i]!=NULL)
    {
	if(lista_adiacenta[i]->info==nod1)
	{
	anterior=lista_adiacenta[i];
	nd=lista_adiacenta[i]->urm;
	while(nd!=NULL)
	{
	if(nd->info==nod2) 
    { 
    printf("Arcul este deja introdus in graf!\n"); 
    return; 
    }
	anterior=nd;
	nd=nd->urm;
	}
	ok=1;
	nod_=(nod*)malloc(sizeof(nod));
	if(nod_==NULL)
	{
	printf("Eroare la alocarea de memorie pentru nod nou!\n");
	exit(EXIT_FAILURE);
	}
	nod_->info=nod2;
	nod_->pondere=pond;
	nod_->urm=NULL;
	anterior->urm=nod_;
	printf("Inserarea arcului a fost efectuata!\n"); 
    return;
    }
	}
	}
	}
	if(ok==0) 
    printf("Inserarea arcului nu poate fi efectuata!\n");
}

nod *indica_nod(int nd)
{
	int i;
	for(i=0;i<n;i++)
	{
	if(lista_adiacenta[i]!=NULL)
	{
	if(lista_adiacenta[i]->info==nd) 
    return lista_adiacenta[i];
	}
	}
	return NULL;
}

void construire_prim()
{
	int nod_inceput,i,j,k,ok,nod1_min,nod2_min;
	nod *nd,*a,*q,*nod_adiac;
	do
	{
	printf("Dati cheia de la care doriti sa inceapa arborele de acoperire minima: "); 
    scanf("%d", &nod_inceput);
	if(indica_nod(nod_inceput)==NULL) 
	printf("Nodul %d nu se afla in graf!\n", nod_inceput);
	}while(indica_nod(nod_inceput)==NULL);
	vizitat[nod_inceput]=1;
	nd=(nod*)malloc(sizeof(nod));
	if(nd==NULL)
	{
	perror("Eroare la alocarea nodului nou!\n");
	return;
	}
	nd->info=nod_inceput;
	nd->pondere=0;
	nd->urm=NULL;
	prim[nod_inceput]=nd;
	printf("Arborele de acoperire minima: \n");
	for(i=2;i<=contor;i++) 
	{
    minim=99999;
	for(j=0;j<n;j++)
	{
	if(vizitat[j]==1) 
	{
	a=lista_adiacenta[j]->urm; 
	while(a!=NULL)
	{	
	ok=0;//presupunem ca nu avem muchie de la j la a->info
	for(k=0;k<n;k++)
	{
	if(vizitat[k]==1&&k!=j&&a->info==k)
	{						
    ok = 1;
	break;
	}
	}
	if(a->pondere<minim&&ok==0) //daca am gasit o muchie cu o pondere mai mica decat cea curenta si a carei extremitati finale nu exista
	{
	minim=a->pondere;
	nod1_min=j;
	nod2_min=a->info;
	}
	a = a->urm;
	}
	}
	}
	cost_minim=cost_minim+minim;
    vizitat[nod2_min]=1;
    nd=(nod*)malloc(sizeof(nod));
	if(nd==NULL)
	{
	printf("Eroare la alocarea noului nod!\n");
	return;
	}
	nd->info=nod2_min;
	nd->pondere=0;
	nd->urm=NULL;
	prim[nod2_min]=nd;
		
	q=prim[nod1_min];
	a=prim[nod1_min]->urm;
	while(a!=NULL)
	{
	q=a;
	a=a->urm;
	}
	nod_adiac=(nod*)malloc(sizeof(nod));
	if(nod_adiac==NULL)
	{
	printf("Eroare la alocarea noului nod!\n");
	return;
	}
	nod_adiac->info=nod2_min;
	nod_adiac->pondere=minim;
	nod_adiac->urm=NULL;
	q->urm=nod_adiac;
    q=prim[nod2_min];
	a=prim[nod2_min]->urm;
	while(a!=NULL)
	{
	q=a;
	a=a->urm;
	}
	nod_adiac=(nod*)malloc(sizeof(nod));
	if(nod_adiac==NULL)
	{
	printf("Eroare la alocarea noului nod!\n");
	return;
	}
	nod_adiac->info=nod1_min;
	nod_adiac->pondere=minim;
	nod_adiac->urm=NULL;
	q->urm=nod_adiac;
	printf("Muchia: %d - %d cu ponderea: %d\n", nod1_min, nod2_min, minim);
	}
}

void traversare_graf()
{
	int i;
	struct nod *nd;
	for(i=0;i<n;i++)
	{
	if(lista_adiacenta[i]!=NULL)
	{
	nd=lista_adiacenta[i]->urm;
	if(nd==NULL)
	{
	printf("Nod cu grad extern 0: %d\n", lista_adiacenta[i]->info);
	}
	else
	{
	while(nd!=NULL)
	{
	printf("Arcul: %d - %d cu ponderea: %d\n",lista_adiacenta[i]->info,nd->info,nd->pondere);
	nd=nd->urm;
	}
	}
	}
	}
}

void traversare_arbore()
{
	int i;
	struct nod *nd;
	for(i=0;i<n;i++)
	{
	if(prim[i]!=NULL)
    {
	nd=prim[i]->urm;
	if(nd!=NULL)
	{
	while(nd!=NULL)
	{
	printf("Arcul: %d - %d cu ponderea: %d\n",prim[i]->info,nd->info,nd->pondere);
	nd=nd->urm;
	}
	}
	}
	}
}

int main()
{
	int opt,nd,nod1,nod2,pond;
	do
	{
		printf("\n1.Initializare graf\n");
		printf("2.Initializare arbore\n");
		printf("3.Inserare nod\n");
		printf("4.Inserare muchie\n");
		printf("5.Construire prim\n");
		printf("6.Traversare graf\n");
		printf("7.Traversare arbore\n");
		printf("0.Iesire\n");
		printf("Optiunea dumneavoastra: "); 
        scanf("%d",&opt);
		switch(opt)
		{
		case 1:
		initializare_graf();
		break;
		case 2:
		initializare_arbore();
		break;
		case 3:
		{
		printf("Nodul pe care doriti sa il inserati: "); 
        scanf("%d",&nd);
		inserare_nod(nd);
		}
		break;
		case 4:
		{
		printf("Nod1 muchie: "); 
        scanf("%d",&nod1);
		printf("Nod2 muchie: "); 
        scanf("%d",&nod2);
		printf("Ponderea: "); 
        scanf("%d",&pond);
		cost_total=cost_total+pond;
		inserare_arc(nod1,nod2,pond);
		inserare_arc(nod2,nod1,pond);
		}
		break;
		case 5:
		construire_prim();
		printf("Costul minim: %d\n",cost_minim);
		break;
		case 6:
		printf("Costul total: %d\n",cost_total);
		traversare_graf();
		break;
		case 7:
		printf("Costul minim: %d\n",cost_minim);
		traversare_arbore();
		break;
		case 0:
		exit(0);
		break;
		default:
		printf("Optiune gresita!\n");
		break;
		}
	} while (1);
	return 0;
}