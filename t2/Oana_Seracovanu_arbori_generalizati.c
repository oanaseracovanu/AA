#include <stdio.h>
#include <stdlib.h>

typedef struct arbore 
{
	unsigned long int tati;
	unsigned int chei;
}arbore;

arbore *A;
FILE *g;
unsigned long int contor=0, N;

void intializare(arbore *A)
{
	int i;
	for(i=0;i<N;i++)
	{
		A[i].chei=0;
		A[i].tati=0;
	}
}

arbore *inserare(unsigned int nod, arbore *A, unsigned int tata)
{
	unsigned long int i, pozitie;
	if (tata==0)
	{
		A[0].chei=nod;
		A[0].tati=0;
		contor++;
	}
	else
	{
		for (i=0;i<N;i++)
		{
			if (A[i].chei==tata)
			{
				pozitie=i;
				break;
			}
		}
		A[contor].tati=pozitie+1;
		A[contor].chei=nod;
		contor++;
	}
	return A;
}

unsigned int tata(unsigned int nod, arbore *A)
{
	unsigned long int i;
	for(i=0;i<N;i++)
	if(A[i].chei==nod)
	{
		return A[i].tati;
	}
	return -1;
}

unsigned int primul_fiu(unsigned int nod, arbore *A)
{
	unsigned long int i;
	unsigned int fiu=0;
	for(i=0;i<N;i++)
	{
		if(A[i].tati==nod) 
        {
		fiu=A[i].chei; 
        return fiu;
        }
	}
	return -1;
}

unsigned int frate_dreapta(unsigned int nod, arbore *A)
{
	unsigned long int i;
	for(i=0;i<N;i++)
	{
		if(A[i].chei==nod)
		if(A[i].tati==A[i + 1].tati) 
        { 
        return A[i + 1].chei; 
        }
	}
	return -1;
}

unsigned int radacina(arbore *A)
{
	if(A==NULL) 
    return 0;
	else 
    return A[0].chei;
}

unsigned int cheie(unsigned long int index, arbore *A)
{
	return A[index].chei;
	return -1;
}

void preordine(unsigned int nod)
{
	unsigned long int i;
	if(nod!=0) 
    fprintf(g,"%u ",nod);
	for(i=0;i<N;i++)
	{
		if(A[A[i].tati-1].chei==nod) preordine(A[i].chei);
	}
}

void postordine(unsigned int rad)
{
	unsigned long int i;
	for(i=0;i<N;i++)
	{
		if(A[A[i].tati-1].chei==rad) postordine(A[i].chei);
	}
	if(rad!=0) fprintf(g,"%u ",rad);
}

void inordine(unsigned int rad)
{
	unsigned long int i;
	unsigned int fiu;
	fiu=primul_fiu(rad, A);
	if(fiu==0) 
	fprintf(g,"%u ",rad);
	else
	{
		inordine(fiu);
		if(rad!=0) 
		fprintf(g,"%u ",rad);
		for(i=0;i<N;i++)
		if(A[A[i].tati-1].chei==rad && A[i].chei!=fiu) 
		inordine(A[i].chei);
	}
}

void suprimare(unsigned int nod, arbore *A)
{
	unsigned long int i,j;
	for(j=0;j<N;j++)
	if(A[j].chei==nod) 
    break;
	A[j].tati=0;
	for(i=0;i<N;i++)
	if(A[A[i].tati-1].chei==nod) 
	suprima(A[i].chei,A);
}

arbore *stergere_suprimate(arbore *A)
{
	unsigned long int i,j;
	for(i=1;i<N;i++)
	{
		if(A[i].tati==0)
		{
			for(j=i;j<N-1;j++)
			{
				A[j].tati=A[j+1].tati;
				A[j].chei=A[j+1].chei;
			}
			N--;
			i--;
		}
	}
	return A;
}

int main(int argc, char *argv[])
{
	unsigned int nod,tatal,fiu;
	unsigned long int i;
    FILE *f;
	A=intializare(A);
	f=fopen(argv[1],"rb");
	if(f==NULL)
	{
		printf("Fisierul nu poate fi deschis\n");
		exit(EXIT_FAILURE);
	}
	g=fopen("OUTPUT.DAT","w");
	if(g==NULL)
	{
		printf("Fisierul nu poate fi deschis\n");
		exit(EXIT_FAILURE);
	}
	fseek(f,0,SEEK_END); 
	N=ftell(f);
	N=N/sizeof(unsigned int);
	fseek(f,0,SEEK_SET); 
	A=(arbore*)malloc(N*sizeof(arbore));
	if(A==NULL)
	{
		printf("Eroare la alocare\n");
		exit(1);
	}
	while(!feof(f))
	{
		fscanf(f,"%u",&fiu);
		fscanf(f,"%u",&tatal);
		A=inserare(fiu,A,tatal);
	}
	printf("Vectorul de tati este: \n");
	for(i=0;i<N;i++)
	{
		printf("%lu ", A[i].tati);
	}
	printf("\n");
	printf("Vectorul de valori este: \n");
	for(i=0;i<N;i++)
	{
	printf("%u ",A[i].chei);
	}
	printf("\n");
	printf("Nodul pentru care cautam tatal: "); 
    scanf("%u", &nod);
	printf("Tatal nodului cu cheia: %u este: %u\n",nod,tata(nod,A));
	printf("Nodul pentru care cautam primul fiu: ");
    scanf("%u", &nod);
	printf("Cel mai din stanga fiu al nodului: %u este: %u\n", nod, primul_fiu(nod,A));
	printf("Nodul pentru care cautam fratele dreapta: "); 
    scanf("%u", &nod);
	printf("Fratele din dreapta al nodului: %u este: %u\n",nod,frate_dreapta(nod,A));
	printf("Nodul pentru care returnam cheia: ");
	scanf("%u",&nod);
	printf("Cheia este: \n",cheie(nod,A));
	printf("Radacina arborelui: %u\n", radacina(A));
	printf("Nodul pe care il suprimam: "); 
    scanf("%u", &nod);
	if(A[0].chei==nod) 
    { 
        printf("Arbore vid\n"); 
        A=intializare(A); 
    }
	else 
    {
		suprimare(nod, A);
		A=stergere_suprimare(A);
		printf("Vectorul de tati este: \n");
		for(i=0;i<N;i++)
		{
			printf("%lu ", A[i].tati);
		}
		printf("\n");
		printf("Vectorul de valori este: \n");
		for(i=0;i<N;i++)
		{
			printf("%u ", A[i].chei);
		}
	}
	fprintf(g,"\n");
	inordine(A[0].chei);
	fprintf(g,"\n");
	preordine(A[0].chei);
	fprintf(g,"\n");
	postordine(A[0].chei);
	free(A);
	fclose(f);
	fclose(g);
	return 0;
}