#include<stdio.h>
void main(){
	int i,n,s,lm,pm,c,ans,ot,index;
	printf("Enter size of physical memory:");
	scanf("%d",&pm);
	printf("Enter size of logical memory:");
	scanf("%d",&lm);
	printf("Enter page size:");
	scanf("%d",&s);
	int pt[lm/s];
	n=pm/s;
	printf("Allocate indices to PageTable(0-%d):\n",n-1);
	for(i=0;i<lm/s;i++){
		printf("pt[%d]:",i);
		scanf("%d",&pt[i]);
	}
	printf("Enter logical memory address to view its address in physical memory:");
	scanf("%d",&c);
	ot=c%s;
	index=c/s;
	ans=pt[index]*s+ot;
	printf("Logical Address %d maps to physical address %d\n",c,ans);
}
