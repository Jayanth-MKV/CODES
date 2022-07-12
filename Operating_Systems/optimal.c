#include<stdio.h>

int find_far(int ind,int a[],int n,int frame[],int no){
    int i,j,k=0,pos=0,np;
    for(i=0;i<no;i++){
        np=0;
        for(j=ind;j<n;j++){
            if(frame[i]==a[j]){
               
		if(k<j){ k=j;
                pos=i;
		}
                np=1;
                break;
            }
        }

    if(np==0){
        pos=i;
        break;
    }

    }
    
    return pos;
}

int main()
{
    int i,j,n,no,k=0,count=0,cnt=0;
    printf("\n ENTER THE NUMBER OF PAGES:\n");
    scanf("%d",&n);
    int a[n];
    printf("\n ENTER THE PAGE NUMBER :\n");
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
            
            br=1;
            break;
        }
        else if(frame[j]==-1){
            frame[j]=a[i];
            
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
        int pos=find_far(i,a,n,frame,no);
        frame[pos]=a[i];
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
