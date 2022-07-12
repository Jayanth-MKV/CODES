#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

struct P{
int AT,BT,WT,FT,ST,TAT,pos;
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
}

int c=n;
int bt[n];
int time=0,mini=INT_MAX;
int index=0;
for(i=0;i<n;i++){
	bt[i]=p[i].BT;
}



int tot_wt,tot_tat;
tot_wt=0;
tot_tat=0;
bool flag=false;
while(c!=0){

for(i=0;i<n;i++){
	if(p[i].AT<=time && mini>bt[i] && bt[i]>0){
	index=i;
	mini=bt[i];		
	flag=true;
	}
}

// if at =1 then loop gets out  hence set flag to false

if(!flag){
	time++;
	continue;
}


bt[index]--;
mini=bt[index];
if(mini==0){
        mini=INT_MAX;
}
time++;
if(bt[index]==0){
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
printf("\tStart time");
printf("\tFinal time");
printf("\tWait Time ");
printf("\tTurnAround Time \n");


for(i=0;i<n;i++){
printf("%d \t\t",p[i].pos);
printf("%d \t\t",p[i].AT);
printf("%d \t\t",p[i].BT);
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
//printf("Hii All");
return 0;
}

