#include<stdio.h>
#include<limits.h>
void print(int n,int ps[],int bt[],int blk[],int sp[],int ep[],int emp[],int emp_size[] ){
        int i;
        printf(" PS \t BT \t Alloc \t Start \t End \t empty \t empty_size \n");
        for(i=0;i<n;i++)
        {
                printf("%d \t %d \t %d \t %d \t %d \t %d \t %d \n",ps[i],bt[i]==INT_MAX?0:bt[i],blk[i]!=-1?blk[i]:0,sp[i]!=-1?sp[i]:0,ep[i]!=-1?ep[i]:0,emp[i]!=-1?emp[i]:0,emp_size[i]!=-1?emp_size[i]:0);
        }
}

int main()
{
int mem_size,n,i, temp,p=0;
int time;
printf("Enter total memory available : ");
scanf("%d",&mem_size);

printf("\nEnter the number of processes ");
scanf("%d",&n);

int blk[n],emp_size[n],ps[n],bt[n],bt_main[n],sp[n],ep[n],pos,emp[n];
printf("\nEnter the Memory required for OS ");
scanf("%d",&pos);

printf("Enter memory required for processes ");
for(i=0;i<n;i++)
{
scanf("%d",&ps[i]);
blk[i]=-1;sp[i]=-1;ep[i]=-1;emp[i]=-1;emp_size[i]=-1;
}

printf("Enter time required for processes : ");
for(i=0;i<n;i++)
{
scanf("%d",&bt_main[i]);
bt[i]=bt_main[i];
}

printf("\nEnter the Time Instance ");
scanf("%d",&time);

printf("Memory allocated for OS : %d\n",pos++);

print(n,ps,bt,blk,sp,ep,emp,emp_size);
temp=mem_size-pos+1;
int cnt=0;
for(i=0;i<n;i++)
{
if(ps[i]<=temp)
{
blk[i]=1;
sp[i]=pos;
ep[i]=pos+ps[i]-1;
pos=pos+ps[i];
temp-=ps[i];
}
else
{
blk[i]=0;
}
}
if(temp>0){
emp[cnt]=pos;
emp_size[cnt]=temp;
cnt++;
}
int frag=0;
int t=time,j;
print(n,ps,bt,blk,sp,ep,emp,emp_size);

while(t>0){
int min=INT_MAX;
int index=-1;
for(i=0;i<n;i++){
if(blk[i] && bt[i]<=t && bt[i]<min){
index=i;
min=bt[i];
}
}
if(index==-1){
break;
}
t-=bt[index];
bt[index]=INT_MAX;
int u=sp[index];
int v=ep[index];
// printf("Before t-%d cnt-%d u-%d v-%d \n",t,cnt,u,v);
if(cnt){
for(int k=0;k<n;k++){      
if( emp[k]!=-1){
if(emp[k]==ep[index]+1){
v=v+emp_size[k];
emp[k]=-1;
emp_size[k]=-1;
}
if(emp[k]+emp_size[k]==sp[index]){
u=emp[k];
emp[k]=-1;
emp_size[k]=-1;
}
}
}
}
printf("After t-%d cnt-%d u-%d v-%d \n",time-t,cnt,u,v);
ep[index]=-1;
sp[index]=-1;
int mem=v-u+1;
int k=0;
for(j=0;j<n;j++){
if(blk[j]==0  && ps[j]<=mem){
blk[j]=1;
sp[j]=u;
ep[j]=sp[j]+ps[j]-1;
k=v+1-u-ps[j];
mem=k;
u=u+ps[j];
j=0;
}
}
if(k!=0){
emp[cnt]=u;
emp_size[cnt]=k;
cnt++;
}
else{
emp[cnt]=u;
emp_size[cnt]=mem;
cnt++;
}
print(n,ps,bt,blk,sp,ep,emp,emp_size);
}
for(i=0;i<n;i++){
if(emp_size[i]!=-1){
frag+=emp_size[i];
}
}
printf("\nTotal External Fragmentation is %d\n",frag);
return 0;
}