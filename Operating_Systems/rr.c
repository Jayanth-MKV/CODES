#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

struct P{
int AT,BT,ST,WT,FT,TAT,pos;
};

void swap(struct P * a,struct P * b){
struct P temp=*a;
*a=*b;
*b=temp;
}

int quant;
int main(){
int n,i;
printf("Enter the no. of processes :");
scanf("%d",&n);
struct P p[n];
printf("Enter the quantum  \n");
scanf("%d",&quant);

for(i=0;i<n;i++){
printf("Enter the process number \n");
scanf("%d",&(p[i].pos));
printf("Enter the Arrival time of process - %d \n",p[i].pos);
scanf("%d",&(p[i].AT));
printf("Enter the Burst time of process - %d \n",p[i].pos);
scanf("%d",&(p[i].BT));
}

for(i=0;i<n-1;i++){
        if(p[i].AT>p[i+1].AT){
		swap(&p[i],&p[i+1]);	
	}
}



int c=n,b[n],a[n],s[n];
int time=0,mini=INT_MAX;
int index=-1;
for(i=0;i<n;i++){
        b[i]=p[i].BT;
	a[i]=p[i].AT;
	s[i]=-1;
}


int tot_wt,tot_tat;
tot_wt=0;
tot_tat=0;
bool flag=false;
while(c!=0){
mini=INT_MAX;
flag=false;
for(i=0;i<n;i++){
        if(a[i]<=time+0.1 &&mini>a[i] && b[i]>0){
	index=i;
        mini=a[i];
	flag=true;
	}
}

// if at =1 then loop gets out  hence set flag to false

if(!flag){
        time++;
        continue;
}
if(s[index]==-1){
s[index]=time;
p[index].ST=time;
}

if(b[index]<=quant && b[index]>0){
	time+=b[index];
	b[index]=0;
}
else if(b[index]>0){
time+=quant;
b[index]-=quant;
a[index]=time+0.1;

}

if(b[index]==0){
c--;
p[index].FT=time;
p[index].WT=p[index].FT-p[index].AT-p[index].BT;
tot_wt+=p[index].WT;
p[index].TAT=p[index].BT+p[index].WT;
tot_tat+=p[index].TAT;
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

return 0;
}

