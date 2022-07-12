#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

struct P{
int AT,BT,WT,FT,ST,TAT,PR,pos;
};

int main(){
int n,i;
printf("Enter the no. of processes :");
scanf("%d",&n);
struct P p[n];
for(i=0;i<n;i++){
printf("Enter the process number \n");
scanf("%d",&(p[i].pos));
printf("Enter the Arrival time of process - %d \n",p[i].pos);
scanf("%d",&(p[i].AT));
printf("Enter the Burst time of process - %d \n",p[i].pos);
scanf("%d",&(p[i].BT));
printf("Enter the priority of process - %d \n",p[i].pos);
scanf("%d",&(p[i].PR));

}

int c=n;
int pr[n];
int time=0,maxi=INT_MIN;
int index=0;
for(i=0;i<n;i++){
        pr[i]=p[i].PR;
}


int tot_wt,tot_tat;
tot_wt=0;
tot_tat=0;
bool flag=false;
while(c!=0){

for(i=0;i<n;i++){
        if(p[i].AT<=time && maxi<pr[i]){
        index=i;
        maxi=pr[i];
        flag=true;
        }
}

// if at =1 then loop gets out  hence set flag to false

if(!flag){
        time++;
        continue;
}

p[index].BT--;
time++;
if(p[index].BT==0){
pr[index]=INT_MIN;
maxi=INT_MIN;
c--;
p[index].FT=time;
p[index].WT=p[index].FT-p[index].AT-p[index].BT;
tot_wt+=p[index].WT;
p[index].TAT=p[index].BT+p[index].WT;
tot_tat+=p[index].TAT;
p[index].ST=p[index].WT+p[index].AT;
flag=false;
}
}



printf("Process number ");
printf("Arrival time ");
printf("Burst time ");
printf("priority     ");
printf("\tStart time");
printf("\tFinal time");
printf("\tWait Time ");
printf("\tTurnAround Time \n");


for(i=0;i<n;i++){
printf("%d \t\t",p[i].pos);
printf("%d \t\t",p[i].AT);
printf("%d \t\t",p[i].BT);
printf("%d \t\t",p[i].PR);
printf("%d \t\t",p[i].ST);
printf("%d \t\t",p[i].FT);
printf("%d \t\t",p[i].WT);
printf("%d \n",p[i].TAT);

}
double avg_wt,avg_tat;
avg_wt=tot_wt/(float)n;
avg_tat=tot_tat/(float)n;

printf("The average wait time is : %lf\n",avg_wt);
printf("The average TurnAround time is : %lf\n",avg_tat);

return 0;
}

