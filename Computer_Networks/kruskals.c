#include <stdio.h>
#include<limits.h>
#define INF INT_MAX

int find(int i,int* a)
{
    while(a[i]!=-1)
    {
	i=a[i];
    }
    return i;
}
int check_loop(int i,int j,int *a)
{
    if(i!=j)
    {
        a[j]=i;
        return 1;
    }
    return 0;
}

int main(){

printf("Enter the number of vertices\n");
int n,i,j;
scanf("%d",&n);
int v[n][n],parent[n];
for(i=0;i<n;i++){
for(j=0;j<n;j++){
v[i][j]=INF;
}
parent[i]=-1;
}

int e,x,y,w;
printf("Enter the number of edges\n");
scanf("%d",&e);
for(i=0;i<e;i++){
printf("Enter the vertices of the edge - %d\n",i+1);
scanf("%d %d",&x,&y);
printf("Enter the edge weight\n");
scanf("%d",&w);
v[x][y]=w;
v[y][x]=w;

}

int c=1;
int mini=INT_MAX;
int sum=0;
while(c<n){
mini=INF;
x=0;
y=0;
int a,b;
for(i=0;i<n;i++){
for(j=0;j<n;j++){

if(mini>v[i][j]){
mini=v[i][j];
x=a=i;
y=b=j;
}

}
}

x=find(x,parent);
y=find(y,parent);
if(check_loop(x,y,parent))
        {
            // printing edges
            printf("%d edge (%d,%d) =%d\n",c++,a,b,mini);
            sum +=mini;
        }
        v[a][b]=v[b][a]=INF;
}
printf("The mincost is : %d \n",sum);
//for(i=0;i<n;i++){
//	printf("%d ",parent[i]);
//}
return 0;
}

