#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define n 100
#define magic -31337
int contor=0;

struct ponderi 
{
	int pondere;
	struct ponderi *p_urm;
};

struct nod
{
	int info,pond,cheie;
	struct nod *urm;
	struct ponderi *p;
};

struct nod *array[n];

void initializare()
{
    int i;
    struct nod *actual, *aux;
    for(i=0;i<n;i++)
    {
        if(array[i]!=NULL)
        {
            actual=array[i]->urm;
            free(array[i]);
            while(actual!=NULL)
            {
                aux=actual;
                actual=actual->urm;
                free(actual);
            }
        }
        array[i]=NULL;
    }
}

int graf_vid()
{
    int i;
    for(i=0;i<contor;i++)
    if(array[i]!=NULL)
    return 0;
    return 1;
}

int graf_plin()
{
    int i;
    int contor_vert=0;
    int contor_arc=0;
    struct nod *actual;
    for(i=0;i<n;i++)
    if(array[i]!=NULL)
    contor_vert++;
    if(contor_vert<n)
    return 0;
    for(i=0;i<n;i++)
    if(array[i]!=NULL)
    actual=array[i]->urm;
    else
    continue;
    while(actual!=NULL)
    {
        contor_arc++;
        actual=actual->urm;
    }
    if(contor_arc==n*(n-1))
    return 1;
    return 0;
}

int cheie_elem(int pozitie)
{
    int i;
    for(i=0;i<n;i++)
    if(array[i]!=NULL)
    if(array[i]->cheie==pozitie)
    return array[i]->cheie;
    if(array[i]==NULL)
    {
        printf("Nodul nu se afla in graf!\n");
        return magic;
    }
    return magic;
}

int cauta_cheie(int nd)
{
    int i;
    for(i=0;i<contor;i++)
    if(array[i]!=NULL)
    if(array[i]->cheie==nd)
    return 1;
    return 0;
}

int indica_nod(int nd)
{
    int i;
    for(i=0;i<contor;i++)
    if(array[i]!=NULL)
    if(array[i]->cheie==nd)
    return array[i]->cheie;
    return 0;
}

int indica_arc(int cheieA,int cheieB)
{
    int i,dist=0,index=-1,k=0;
    struct nod *actual;
    for(i=0;i<contor;i++)
    if(array[i]!=NULL)
    if(array[i]->cheie==cheieA)
    {
    index=i;
    break;
    }
    if(index!=-1)
    {
        actual=array[index]->urm;
        while(actual!=NULL)
        {
            dist++;
            if(array[index]->urm->cheie==cheieB)
            {
                k=1;
                break;
            }
            actual=actual->urm;
        }
        if(k==1)
        return dist;
        return magic;
    }
    return magic;
}

int arc_vid(int arc)
{
    if(arc==magic)
    return 1;
    return 0;
}

void inserare_nod(int nd)
{
    int pnd,inform,i;
    if(graf_plin())
    printf("Nu mai putem insera, graful este deja plin!\n");
    for(i=0;i<contor;i++)
    if(array[i]!=NULL)
    if(array[i]->cheie==nd)
    {
        printf("Nodul acesta a fost inserat deja!\n");
        return;
    }
    array[contor]=(struct nod*)malloc(sizeof(struct nod));
    array[contor]->cheie=nd;
    array[contor]->urm=NULL;
    array[contor]->info=inform;
    array[contor]->pond=pnd;
    contor++;
}

void inserare_arc(int cheieA,int cheieB)
{
    int i,pozitie=-1;
    struct nod *p,*nou;
    for(i=0;i<n;i++)
    if(i==cheieA)
    {
        pozitie=i;
        break;
    }
    if(pozitie==-1 || pozitie>=n)
    printf("Nu se poate insera!\n");
    p=array[pozitie];
    if(p==NULL)
    {
        nou=(struct nod*)malloc(sizeof(struct nod));
        nou->cheie=cheieB;
        nou->urm=NULL;
        array[pozitie]=nou;
    }
    else
    {
        while(p->urm!=NULL)
        p=p->urm;
        nou=(struct nod*)malloc(sizeof(struct nod));
        nou->cheie=cheieB;
        nou->urm=NULL;
        p->urm=nou;
    }
}

void suprima_nod(int nd)
{
    int i,j,pozitie=-1;
    for(i=0;i<contor;i++)
    if(array[i]!=NULL)
    if(array[i]->cheie==nd)
    {
        pozitie=i;
        break;
    }
    for(j=pozitie;j<contor;j++)
    if(array[j]!=NULL)
    {
        free(array[j]);
        break;
    }
    else
    {
        printf("Nu exista nod de sters pe %d\n",pozitie);
        return;
    }
    for(j=pozitie;j<contor-1;j++)
    if(array[j]!=NULL)
    array[j]->cheie=array[j+1]->cheie;
    contor--;
}

void suprima_arc(int pozitie,int nd)
{
    int i,pozitie=-1;
    struct nod *prim,*p,*sterg;
    for(i=0;i<contor;i++)
    if(array[i]!=NULL)
    if(array[i]->cheie==pozitie)
    {
        pozitie=i;
        break;
    }
    for(i=pozitie;i<contor;i++)
    {
        if(array[i]!=NULL)
        {
            prim=array[i];
            p=prim;
            if(p)
            {
                if(p->cheie==nd)
                {
                    sterg=prim;
                    prim=sterg->urm;
                    free(sterg);
                }
                else
                {
                    while(p->urm && p->urm->cheie!=nd)
                    p=p->urm;
                    if(p->urm==NULL)
                    printf("Nu exista acest nod!\n");
                    else if(p->urm->cheie==nd)
                    {
                        sterg=p->urm;
                        p->urm=sterg->urm;
                        free(sterg);
                    }
                }
            }
            else
            printf("Nu exista acest arc!\n");
        }
        break;
    }
}

void actualizare(int x,int y)
{
    int i;
    for(i=0;i<contor;i++)
    if(array[i]!=NULL)
    if(array[i]->cheie==x)
    {
    array[i]->cheie=y;
    break;
    }
}

int furnizeaza_nod(int x)
{
    int i;
    for(i=0;i<n;i++)
    if(array[i]!=NULL)
    if(array[i]->cheie==x)
    return array[i]->cheie;
    return -1;
}

int main()
{
    int opt,nd,ar,k,cheieA,cheieB;
    struct nod *arc=NULL;
    do
    {
        printf("\n");
        printf("0.Iesire\n");
        printf("1.Initializare graf\n");
        printf("2.Graf vid\n");
        printf("3.Graf plin\n");
        printf("4.Cheie element graf\n");
        printf("5.Cauta cheie graf\n");
        printf("6.Indica nod\n");
        printf("7.Indica arc\n");
        printf("8.Arc vid\n");
        printf("9.Inserare nod\n");
        printf("10.Inserare arc\n");
        printf("11.Suprimare nod\n");
        printf("12.Suprimare arc\n");
        printf("13.Actualizare nod\n");
        printf("14.Furnizeaza nod\n");
        printf("15.Traversare graf\n");
        printf("Optiunea dumneavoastra: ");
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
            initializare();
            break;
            case 2:
            if(graf_vid())
            printf("Graful este vid\n");
            else
            printf("Graful nu este vid\n");
            break;
            case 3:
            if(graf_plin())
            printf("Graful este plin\n");
            else
            printf("Graful nu este plin\n");
            break;
            case 4:
            printf("Nodul pe care doriti sa il cautati: ");
            scanf("%d",&nd);
            if(cheie_elem(nd))
            printf("Nodul %d este al %d-lea element din graf",nd,cheie_elem(nd));
            else
            printf("Nodul nu se afla in graf\n");
            break;
            case 5:
            printf("Nodul pe care doriti sa il verificati daca exista: ");
            scanf("%d",&nd);
            k=cauta_cheie(nd);
            if(k)
            printf("Nodul exista\n");
            else
            printf("Nodul nu exista\n");
            break;
            case 6:
            printf("Nodul pe care doriti sa il gasiti: ");
            scanf("%d",&nd);
            if(indica_nod(nd))
            printf("Nodul este: %d\n",indica_nod(nd));
            else
            printf("Nodul nu exista!\n");
            break;
            case 7:
            printf("Nodul A: ");
            scanf("%d",&cheieA);
            printf("Nodul B: ");
            scanf("%d",&cheieB);
            ar=indica_arc(cheieA,cheieB);
            if(ar)
            printf("Arcul este: %d\n",ar);
            else
            printf("Arcul nu exista!\n");
            break;
            case 8:
            printf("Arcul de verificat: ");
            scanf("%d",&ar);
            if(arc_vid(ar))
            printf("Arcul nu exista!\n");
            else
            printf("Exista arcul\n");
            break;
            case 9:
            printf("Nodul pe care doriti sa il inserati: ");
            scanf("%d",&nd);
            inserare_nod(nd);
            break;
            case 10:
            printf("Nodul A: ");
            scanf("%d",&cheieA);
            printf("Nodul B: ");
            scanf("%d",&cheieB);
            inserare_arc(cheieA,cheieB);
            break;
            case 11:
            printf("Nodul pe care doriti sa il suprimati: ");
            scanf("%d",&nd);
            suprima_nod(nd);
            break;
            case 12:
            printf("Nodul A: ");
            scanf("%d",&cheieA);
            printf("Nodul B: ");
            scanf("%d",&cheieB);
            suprima_arc(cheieA,cheieB);
            break;
            case 13:
            printf("Nodul pe care doriti sa il actualizati: ");
            scanf("%d",&cheieA);
            printf("Cu ce vreti sa fie actualizat: ");
            scanf("%d",&cheieB);
            actualizare(cheieA,cheieB);
            break;
            case 14:
            printf("Nodul care doriti sa va fie furnizat: ");
            scanf("%d",&nd);
            if(furnizeaza_nod(nd)==0)
            printf("Nodul nu poate fi furnizat!\n");
            else
            printf("Nodul furnizat: %d\n",nd);
        }
    } while (1);
    
    return 0;
}