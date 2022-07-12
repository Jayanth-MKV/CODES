#include<stdio.h>

struct P{
int AT,BT,WT,FT,ST,TAT,pos;
};

void swap(struct P *a,struct P *b){
struct P temp=*a;
*a=*b;
*b=temp;
}


int main(){
int n,i,j,temp;
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

for(i=0;i<n;i++){
for(j=0;j<n-i-1;j++){
if(p[j].AT>p[j+1].AT){
swap(&p[j],&p[j+1]);
}

}
}

p[0].ST=p[0].AT;
temp=0;

for(i=1;i<n;i++){
temp=p[i-1].ST+p[i-1].BT;
if(p[i].AT>temp){
p[i].ST=p[i].AT;
}
else{
p[i].ST=temp;
}
}



int tot_wt,tot_tat;
tot_wt=0;
tot_tat=0;

for(i=0;i<n;i++){
p[i].WT=p[i].ST-p[i].AT;
tot_wt+=p[i].WT;
p[i].FT=p[i].WT+p[i].AT+p[i].BT;
p[i].TAT=p[i].BT+p[i].WT;
tot_tat+=p[i].TAT;
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
