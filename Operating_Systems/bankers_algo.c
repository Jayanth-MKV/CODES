#include<stdio.h>
#include<stdbool.h>
bool res_req_algo(int m,int n,int max[m][n],int alloc[m][n],int need[m][n],int avail[],int req[n],int p);
bool safety_algo(int m,int n, int max[m][n],int alloc[m][n],int need[m][n],int avail[n] ){
    int work[n],res[m],i,j,k;
        for(i=0;i<n;i++){
        work[i]=avail[i];
        }
        bool finish[m],flag,done=true;
        flag=true;
        for(i=0;i<n;i++){
        finish[i]=false;
        }

 int cnt=0;
while(cnt<m){
        if(!done){
            break;
        }
        for(j=0;j<m;j++){
                done=false;
                if(!finish[j]){
                        flag=true;
                        for(k=0;k<n;k++){
                                if(need[j][k]>work[k]){
                                        flag=false ;
                                        break ;
                                }
                        }

                if(flag){
                        res[cnt++]=j;
                        for(k=0;k<n;k++){
                        work[k]+=alloc[j][k];
                        }
                        finish[j]=true;
                        done=true;
                        }
                }
        }
}

        if(cnt<m){
            printf("Unsafe \n ");
            return false;
        }
        else{
        printf(" It is safe :\n ");
        printf(" Process Order: \n");
        for(i=0;i<m;i++){
        printf("%d ",res[i]);
        }
        printf("\n");
        printf(" Available resources : \n");
        for(i=0;i<n;i++){
        printf("%d ",work[i]);
        }
        printf("\n Continue with the requests \n");
        return true;
        }

}
void fun_for_req(int m,int n,int max[m][n],int alloc[m][n],int need[m][n],int avail[n]){
    int ch=1,p,req[n],i,k,j;
    int dup_alloc[n];
    int dup_need[n];
    int dup_avail[n];
    while(ch!=0){
    printf("Do you want to give requests :\n 1. Yes\n 0. No \n ");
    scanf("%d",&ch);
    if(ch){
        bool flag=true;
        printf("Enter the process to take the request :\n ");
        scanf("%d",&p);
        printf("Enter the requests of the process of :\n ");
        for(i=0;i<n;i++){
        printf(" Type - %d \n ",i+1);
        scanf("%d",&req[i]);
        }
        for(i=0;i<n;i++){
            dup_alloc[i]=alloc[p][i];
            dup_avail[i]=avail[i];
            dup_need[i]=need[p][i];
        }
        
        if(!res_req_algo(m,n,max,alloc,need,avail,req,p)){
            for(i=0;i<n;i++){
            alloc[p][i]=dup_alloc[i];
            avail[i]=dup_avail[i];
            need[p][i]=dup_need[i];
        }
            // print(m,n,max,alloc,need,avail);
            continue;
        }
        else{
            return;
        }
    }
    else{
        printf(" Process completed successfully \n ");
        return;
    }
    }
}
bool res_req_algo(int m,int n,int max[m][n],int alloc[m][n],int need[m][n],int avail[],int req[n],int p){
    int k;
    bool flag=true; 
    for(k=0;k<n;k++){
            if(need[p][k]<req[k]){
                    flag=false;
                    break;
            }
        }
        if(!flag){
            printf(" Request is greater than Need :\n ");
            return false;
        }

        flag=true;

        for(k=0;k<n;k++){
            if(avail[k]<req[k]){
                    flag=false;
                    break;
            }
        }
        if(!flag){
            printf(" Request is greater than Available :\n ");
            return false;
        }

        for(k=0;k<n;k++){
            need[p][k]-=req[k];
            avail[k]-=req[k];
            alloc[p][k]+=req[k];
        }
        // print(m,n,max,alloc,need,avail);
        if(safety_algo(m,n,max,alloc,need,avail)){
            printf(" Request is successfully processed :\n ");
            fun_for_req(m,n,max,alloc,need,avail);
            return true;
        }
        else{
            return false;
        }
}
int main(){
        int m,n,i,j,k;
        printf("Enter the number of processes :\n ");
        scanf("%d",&m);
        printf("Enter the number of resources : \n");
        scanf("%d",&n);       
        int max[m][n] , alloc[m][n] , avail[n] , tot_res[n], tot_alloc[n], need[m][n];
        printf("Enter the total number of resources in : \n");
        for(i=0;i<n;i++){
        printf(" type - %d ", i+1);
        scanf("%d",&tot_res[i]);
        }
        printf("Enter the max elements : \n");
        for(i=0;i<m;i++){
        for(j=0;j<n;j++){
        scanf("%d",&max[i][j]);
        }
        }
        printf("Enter the allocation elements :\n ");
        for(i=0;i<m;i++){
        for(j=0;j<n;j++){
        scanf("%d",&alloc[i][j]);
        }
        }
        for(i=0;i<n;i++){
        int sum=0;
        for(j=0;j<m;j++){
        sum+=alloc[j][i];
        }
        tot_alloc[i]=sum;
        }
        for(i=0;i<n;i++){
        avail[i]=tot_res[i]-tot_alloc[i];
        }
        for(i=0;i<m;i++){
        for(j=0;j<n;j++){
        need[i][j]=max[i][j]-alloc[i][j];
        }
        }
        // print(m,n,max,alloc,need,avail);
    if(safety_algo(m,n,max,alloc,need,avail)){
        fun_for_req(m,n,max,alloc,need,avail);
    }
    else{
        printf(" It is unsafe and deadlock may occur :\n ");
    }
        return 0;
}
