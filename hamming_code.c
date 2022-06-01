#include<stdio.h>
#include<stdbool.h>
#include<math.h>

void send_code(int * a,int *res){

    int i,j=0,r=6,k=0,cnt=0,n=39;
    res[0]=2;
    for(i=1;i<n;i++){
        int p=pow(2,cnt);
        if(i==p){
            res[i]=-1;
            cnt++;
        }
        else{
            res[i]=a[j];
            j++;
        }
    }

    int pr[r],p=0;
    j=0;  
    for(k=0;k<r;k++){
        p=pow(2,k);
        j=p;
        pr[k]=0;
        res[p]=1;
    while(j<n){
        for(i=0;i<p;i++){
        pr[k]=pr[k]^(res[j+i]);
        }
        j+=(p*2);
    }
    if(pr[k]==0){
        res[p]=1;
    }
    else{
       res[p]=0;
    }
    }
}

int rec_code(int *res){
    int i,j=0,r=6,k,n=39;
    // for(i=1;i<n;i++){
    //     int p=pow(2,cnt);
    //     if(i==p){
    //         res[i]=-1;
    //         cnt++;
    //     }
    //     else{
    //         res[i]=a[j];
    //         j++;
    //     }
    // }

    int pr[r],p=0; 
    for(k=0;k<r;k++){
        p=pow(2,k);
        j=p;
        pr[k]=0;
    while(j<n){
        for(i=0;i<p;i++){
        pr[k]=pr[k]^(res[j+i]);
        }
        j+=(p*2);
    }
    printf("%d - %d\n",pr[k],res[p]);
    if(pr[k]!=res[p]){
       return p;
    }
}
return 0;
}

int main(){

    int a[32]={1,1,1,0,0,1,0,1,1,1,0,0,0,0,0,1,1,0,0,1,0,0,1,1,0,0,1,0,1,0,0,1};
    int res[39],i;
    send_code(a,res);
    printf("The sending code is :\n");
    for(i=0;i<39;i++){
        printf("%d ",res[i]);
    }
    printf("\n");
    int ham=rec_code(res);
    printf("The receiving code has %d errors:\n",ham);

    for(i=0;i<39;i++){
        printf("%d ",res[i]);
    }
    printf("\n");

    return 0;
}
