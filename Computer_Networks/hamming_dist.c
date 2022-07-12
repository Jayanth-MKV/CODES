#include<stdio.h>
#include<string.h>


int ham_dist(int m,int n,int a[],int b[]){
	int i,res=0,p;
	p=m-n;
	if(p==0){
	for(i=0;i<m;i++){
	if(a[i]^b[i]){
	res++;
	}
	}
	}
	else if(p<0){
	for(i=0;i<m;i++){
        if(a[i]^b[i]){
        res++;
        }
        }
	res=res+(-p);
	}
	else{
	for(i=0;i<n;i++){
        if(a[i]^b[i]){
        res++;
        }
        }
	res=res+p;
	}
	return res;
}

int main()
{
        int i,j,m,n;
        printf("Enter the length of the stream\n");
	scanf("%d", &m);
	int a[m];	
       	printf("Enter the sending stream\n");
	for(i=0;i<m;i++){
	scanf("%d", &a[i]);
	}
	 printf("Enter the length of the stream\n");
        scanf("%d", &n);
	int b[n];
         printf("Enter the sending stream\n");
        for(i=0;i<n;i++){
        scanf("%d", &b[i]);
        }
	int ham=ham_dist(m,n,a,b);
	if(ham==0){
	printf("No Errors received\n");
	}
	else{
	printf("%d - Errors received\n",ham);
	}

	return 0;
    }

