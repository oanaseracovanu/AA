#include<stdio.h>
#include<stdlib.h>

int main()
{
    int N;
    float a[10];
    float nr,ep;
    int i,nr_pasi;
    FILE *f,*f1;
    if((f=fopen("input.dat","r"))==NULL)
    printf("Nu putem deschide\n");
    else
    {
        fscanf(f,"%d",&N); 
        for(i=0;i<N;i++)
        {
        fscanf(f,"%f",&a[i]);
        fscanf(f,"%f %f",&nr,&ep);
        fclose(f);
        }
    }

    for(i=1;i<=N;i++)
    {
    if(a[i]>a[i-1]) 
    nr_pasi=0;
	while ((a[i]-nr<=ep||nr-a[i]>=ep) && i < N) 
    {   
        nr_pasi++;
    }
    }

    if((f1=fopen("output.dat","w"))==NULL)
    printf("Nu se poate deschide\n");
    else
    {
       fprintf(f1,"Numarul de pasi: %d",nr_pasi);
       fclose(f1);
    }
    return 0;

}