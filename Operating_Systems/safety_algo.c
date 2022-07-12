
 #include<stdio.h>
#include<stdbool.h>

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

		int work[n],res[m];
        for(i=0;i<n;i++){
        work[i]=avail[i];
        }
        bool finish[m],flag,done=true;
        for(i=0;i<m;i++){
        	flag=true;
        for(k=0;k<n;k++){
            if(alloc[i][k]!=0){
                    flag=false ;
                    break ;
            }
        }

        if(flag){	
		finish[i]=true;
		}
		else{        	
        finish[i]=false;
		}

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
            printf("Deadlock occurs \n ");
        }
        else{	
        printf(" Deadlock doesnt occur \n ");
        
        printf(" Process Order: \n");
        for(i=0;i<m;i++){
        printf("%d ",res[i]);
        }
		}


return 0;
}
