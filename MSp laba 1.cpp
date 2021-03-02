# include <iostream>
# include <conio.h>
# include <math.h>
# include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

struct node
{
	int v;
	node *next;
	node(int x, node *t){v=x;next=t;} //ctor!! конструктор
};
typedef node *lnk;
void FMI( int *MI, int *MS, lnk *adj, int n, int m);
void FMS( int *MI, int *MS, lnk *adj, int n, int m);
void FSS(int *MI, int *MS, lnk *adj, int n, int m);
void MS_to_SS(int * MS, lnk *adj, int n);
void SS_to_MI(int * MI,lnk *adj,int n);
void MI_to_MS(int * MI, int *MS, int n, int m);
void printm(int *MI, int *MS, lnk *adj, int n, int m); 
void delmem(int *MI, int *MS, lnk *adj, int n);
void destroy(node *R);

//------------------------------------------------------------

int main()
{
int k;
int *MI, *MS;
int n,m;
lnk * adj;

printf("Vvedite kol-vo vershin : n = ");
	scanf("%d",&n);
	printf("Vvedite kol-vo dug : m = ");
	scanf("%d",&m);
MI = (int *)calloc(n*m, sizeof(int));
MS = (int *)calloc(n*n, sizeof(int));
adj = (lnk *)calloc(n,sizeof(lnk));

printf("Sposob vvoda\n1. Matritsa Intidentnosti\n2. Matritsa Smejnosti\n3. Spisok Smejnosti\n4. Zaversheni programmi\n\nVash vibor :  ");
scanf("%d",&k);
printf("\n");
switch(k)
{
	case 1:	FMI(MI, MS, adj, n, m); break;
	case 2:	FMS(MI, MS, adj, n, m); break;
	case 3:	FSS(MI, MS, adj, n, m); break;
	case 4: return 0;
}
printm(MI, MS, adj, n, m);
delmem(MI, MS, adj, n);
getch(); 
return 0;
}

//-------------------------------------------------------------

void FMI( int *MI, int *MS, lnk *adj, int n, int m)
{
    printf("Matritsa Intidentnosti\n");
    for(int i=0;i<m;i++) 
		{
			for(int j=0;j<n;j++)
			scanf("%d",(MI+i*n+j));
    	}
    	MI_to_MS(MI, MS, n, m);
		MS_to_SS(MS,adj,n);
	   	
}

//-------------------------------------------------------------

void FMS(int *MI, int *MS, lnk *adj, int n, int m)
{
    printf("Matritsa Smejnosti\n");    
    for(int i=0;i<n;i++) 
		{
			for(int j=0;j<n;j++)
			scanf("%d",(MS+i*n+j));
    	} 
       	MS_to_SS(MS,adj,n);
       	SS_to_MI(MI,adj,n);	
}

void FSS(int *MI, int *MS, lnk *adj, int n, int m)
{
    int tmp;
		printf("Spisok Smejnosti\n ");
    for(int i=0;i<n;i++)
	{
	    printf("\t%d: ", i+1);
			scanf("%d", &tmp);
			while(tmp)
			{
				adj[i]=new node(tmp-1,adj[i]);
			    scanf("%d",&tmp);
	    	}
   	}
   		SS_to_MI(MI,adj,n);
      	MI_to_MS(MI, MS, n, m);
}

//--------------------------------------------------------------

void MS_to_SS( int *MS,lnk *adj, int n)
{
    for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(*(MS+i*n+j))
				adj[i]=new node(j,adj[i]);
}

//--------------------------------------------------------------

void SS_to_MI(int * MI,lnk*adj,int n)
{
    int m=0;
	for(int i=0;i<n;i++)
	{
		lnk tmp=adj[i];
        while(tmp)
		{
			
			if((tmp->v) == i) *(MI+m*n+i)=2;
			
			else{
			*(MI+m*n+i)=-1;
			*(MI+m*n+tmp->v)=1;
		}
		    m++;
            tmp=tmp->next;
        }
	}
}

//--------------------------------------------------------------

void MI_to_MS(int * MI, int *MS, int n, int m)
{
    int i,j,k,l;
		for (i=0;i<m;i++)
		{
        for (j=0;j<n;j++){
	    if(*(MI+i*n+j)==-1) k=j; 
        if(*(MI+i*n+j)==1) l=j; 
		if(*(MI+i*n+j)==2) k=l=j;   	  
  }
  *(MS+k*n+l)=1;
  if(l==k)	*(MS+k*n+l)=2;	
		
    }
}

//--------------------------------------------------------------
void delmem(int *MI, int *MS, lnk *adj, int n){
	free(MI);
	free(MS);

	for(int i=0; i<n; i++) destroy(*(adj+i));
	free(adj);
	printf ("\nPamiat osvobojdena!\n\n");
	printf("\n**********************\n");
			printf("* Uda4nogo dnea :)!! *\n**********************");
}
void destroy(node *R)
{
   node *tmp;
   while(R)
	{
		tmp=R; 
		R=R->next;
		free(tmp);
	}
}

//--------------------------------------------------------------

void printm(int *MI, int *MS, lnk *adj, int n, int m)
{
	int z,l=1;
	
	while(l)
	{
	printf("\n**************************************************");	
	printf("\n\nSposob vivoda\n1.Matritsa Intidentnosti\n2.Matritsa Smejnosti\n3.Spisok Smejnosti\n4.Osvobojdenie pamiati i zavershenie programmi\n");
	printf("\nVash vibor : ");
	scanf("%d",&z);
	switch(z)
	{
		case 1:{
			printf("\nMatritsa Intidentnosti\n   ");
			 	for(int i = 1; i <= n; i++)
			  	printf("n%d ", i);
			  	printf("\n");
      		for(int i = 0; i < m; i++)
			{
			  	printf("v%d ",i+1); 
           	for(int j = 0; j < n; j++)
				printf("%2d ",*(MI+i*n+j));
                printf("\n");
            }
			break;
		}
		case 2:{
			printf("\nMatritsa Smejnosti\n   ");
			for(int i = 1;i <= n; i++)
			  	printf("n%d ", i);
			  	printf("\n");
    		for(int i=0;i<n;i++)
			{
    			printf("n%d ", i+1); 
            	for(int j=0;j<n;j++)
                	printf("%2d ",*(MS+i*n+j));
		    		printf("\n");
		    	}
			break;
		}
		case 3:{
			printf("\nSpisok smeznosti\n");
	      		for(int i=1;i<=n;i++)
				{
					printf("%d : ",i);
				lnk tmp=adj[i-1];
				while(tmp)
				{
		   			printf("%d ",tmp->v+1);
		   			tmp=tmp->next;
				}
			printf("0\n");
		}
			
			break;
		}
		case 4:{
			   l=0 ;
			break;
			}
		
		}
	}
}


