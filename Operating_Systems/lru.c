#include<stdio.h>

int find_min(int t[],int no){
    int i,mini=t[0],pos=0;
    for(i=1;i<no;i++){
        if(mini>t[i]){
            mini=t[i];
            pos=i;
        }
    }
    return pos;
}

int main()
{
    int i,j,n,no,k=0,count=0,cnt=0;
    printf("\n ENTER THE stream length:\n");
    scanf("%d",&n);
    int a[n];
    printf("\n ENTER THE stream :\n");
    for(i=0;i<n;i++)
    scanf("%d",&a[i]);
    printf("\n ENTER THE NUMBER OF FRAMES :");
    scanf("%d",&no);
    int frame[no],t[no];
    for(i=0;i<no;i++)
    frame[i]= -1;
    int br=0;
    printf("\tref string\t page frames\n");
    for(i=0;i<n;i++)
    {
    k=0,br=0;
    printf("%d\t\t",a[i]);  
    for(j=0;j<no;j++){
        if(frame[j]==a[i]){
            cnt++;
            t[j]=cnt;
            br=1;
            break;
        }
        else if(frame[j]==-1){
            frame[j]=a[i];
            cnt++;
            t[j]=cnt;
            count++;
            br=1;
            break;
        }
    }
    
    if(br==1){
        for(j = 0; j < no; ++j){
     printf("%d\t", frame[j]);
     }
     printf("\n");
        continue;
    }
    else{
        int pos=find_min(t,no);
        frame[pos]=a[i];
        cnt++;
        t[pos]=cnt;
        count++;
    }

    for(j = 0; j < no; ++j){
     printf("%d\t", frame[j]);
     }
     printf("\n");

    }   

    printf("Page Fault Is %d",count);
return 0;
}
