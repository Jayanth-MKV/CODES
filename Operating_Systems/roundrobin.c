#include<stdio.h>
#include<limits.h>
struct rr{
        float at,bt,wt,st,tat,ft,y;
};
void main(){
        int n,i=1,j,k,l,t,count,tq,temp,flag=0;
        float avgwt=0,avgtat=0;
        printf("Enter number of processes\n");
        scanf("%d",&n);
        printf("Enter time quantum : ");
        scanf("%d",&tq);
        count=n;
        float a[n],b[n],s[n],sum=0,min;
        struct rr p[n+1];
        while(i<=n){
            printf("Enter process number : ");
            scanf("%d",&t);
            printf("\tEnter arrival time : ");
            scanf("%f",&p[t].at);
            printf("\tEnter burst time : ");
            scanf("%f",&p[t].bt);
            i++;
        }
        for(i=1;i<=n;i++){
            a[i-1]=p[i].at;
            b[i-1]=p[i].bt;
            s[i-1]=-1;
        }
        while(count>0){
            min=INT_MAX;
            temp=0;
            for(i=0;i<n;i++){
		float f=sum+0.1;
                if(a[i]<=f && b[i]>0 && min>a[i]){
                        min=a[i];
                        temp=1;
                        k=i;
                        // printf("a[%d]=%f , b[%d]=%f , k=%d , %f \n", i,a[i],i,b[i],k,sum);
                  }
            }
            if(temp!=1){
                sum++;
                printf("sum in temp : %f \n",sum);

                continue;
            }
            if(s[k]==-1){
                s[k]=sum;
                        }
            if(b[k]<=tq && b[k]>0){
                sum=sum+b[k];
                b[k]=0;
                count--;
                p[k+1].ft=sum;
                printf("sum-1 : %f , %f\n",sum,a[k]);


            }
            else if(b[k]>0){
                b[k]=b[k]-tq;
                sum=sum+tq;
                a[k]=sum+0.1f;
                printf("sum-2 : %f , %f\n",sum,a[k]);

            }
        }
        for(i=1;i<=n;i++){
                p[i].tat=p[i].ft-p[i].at;
                p[i].wt=p[i].tat-p[i].bt;
                p[i].st=s[i-1];
        }
        printf("Process\tat\tbt\tst\tft\twt\ttat\n");
        for(i=1;i<=n;i++){
                avgwt+=p[i].wt;
                avgtat+=p[i].tat;
                printf("p%d\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n",i,p[i].at,p[i].bt,p[i].st,p[i].ft,p[i].wt,p[i].tat);
        }
        printf("The avg wt is = %0.2f\n",avgwt/n);
        printf("The avg tat is = %0.2f\n",avgtat/n);
    }