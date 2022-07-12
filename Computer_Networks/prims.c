#include <stdio.h>
#include<limits.h>
#define INF INT_MAX

int main(){

printf("Enter the number of vertices\n");
int n,i,j;
scanf("%d",&n);
int v[n][n];
for(i=0;i<n;i++){
for(j=0;j<n;j++){
v[i][j]=INF;
}
}

int e,x,y,w;
printf("Enter the number of edges\n");
scanf("%d",&e);
for(i=0;i<e;i++){
printf("Enter the vertices of the edge - %d\n",i+1);
scanf("%d %d",&x,&y);
printf("Enter the edge weight\n");
scanf("%d",&w);
v[x-1][y-1]=w;
v[y-1][x-1]=w;

}

int visited[n];
for(i=0;i<n;i++){
visited[i]=0;
}

visited[0]=1;
int c=n-1;
int mini=INT_MAX;
int sum=0;
while(c!=0){
mini=INF;
x=0;
y=0;
for(i=0;i<n;i++){
if(visited[i]){
for(j=0;j<n;j++){
if(!visited[j]&&v[i][j]){
if(mini>v[i][j]){
mini=v[i][j];
x=i;
y=j;
}
}
}
}
}
if(mini!=INF){
printf("%d - %d => %d\n",x+1,y+1,mini);
visited[y]=1;
sum+=mini;
}
c--;
}
printf("%d :",sum);
return 0;
}
