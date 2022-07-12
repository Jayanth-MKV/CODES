#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct f{

char name[10];
int size;
int index;
int no_blks;
int active;
int seq[20];
int seq_cnt;
};

int l;

bool allocate(struct f list[],int loc,int blks,int disk[],int nob){
int i,cnt=0;
if(l<blks){
    return false;
}
while(cnt<blks){
    int r=rand()%nob;
    if(disk[r]==0){
    list[loc-1].seq[cnt++]=r;
    disk[r]=1;
    l--;
    }
}
list[loc-1].index=list[loc-1].seq[0];
list[loc-1].seq_cnt=cnt;

return true;

}

void create(struct f list[],int loc,int blk_size,int disk[],int nob){
    
    char fn[10];
    int fs,blks;
   
        printf("Enter the file name: ");
        scanf("%s",fn);
        printf("Enter the size of the file: ");
        scanf("%d",&fs);
       
        blks=(fs/blk_size)+((fs%blk_size==0)?0:1);
        printf("No of blocks to allocate : %d\n",blks);

        if(allocate(list,loc,blks,disk,nob)){
            list[loc-1].active=1;
            strcpy(list[loc-1].name,fn);
            list[loc-1].no_blks=blks;
            list[loc-1].size=fs;
            printf(" File created and allocated successfully\n");
        }
        else{
            printf(" File not created nor allocated \n");
        }
      
}


int search(struct f list[],int loc,int blk_size,int disk[],int nob){

printf(" Enter file name to delete \n");
char name[10];
scanf("%s",name);
for(int i=0;i<loc;i++){
    if(strcmp(name,list[i].name)){
        continue;
    }
    else{
        return i;
    }
}

return -1;

}

void delete(struct f list[],int loc,int blk_size,int disk[],int nob){
int pos=search(list,loc,blk_size,disk,nob);
if(pos==-1){
    printf("File not found");
    return;
}
else{
    for(int i=0;i<list[pos].seq_cnt;i++)
    disk[list[pos].seq[i]]=0;
    l+=list[pos].seq_cnt-1;
    list[pos].active=0;
    list[pos].no_blks=0;
    list[pos].index=0;
    list[pos].size=0;
    memset(list[pos].seq, 0, 20);
    strcpy(list[pos].name,"");
    
    printf(" File deleted successfully\n");

}


}

void display(struct f list[],int loc,int blk_size,int disk[],int nob){

    printf("\n Files allocation Details \n");
    printf("Filename start  seq\n");
    for(int i=0;i<loc;i++){
        if(list[i].active==1){
            printf("%s %d\t",list[i].name,list[i].index);
            for(int j=0;j<list[i].seq_cnt;j++)
            printf("%d - ",list[i].seq[j]);
            printf("\n");
        }
    }

    printf(" Disk \n");
    for(int i=0;i<nob;i++){
    printf("%d - ",disk[i]);
    }
    printf("\n");
    char name[10];
    printf("Enter the file name to display\n");
    scanf("%s",name);
    for(int i=0;i<loc;i++){
        if(!strcmp(name,list[i].name)){
        printf("----Filename - %s----\n",list[i].name);
        printf("Size : %d\n No_of_blocks : %d\n Index-block - %d\n",list[i].size,list[i].no_blks,list[i].index);
        return;
        }
    }
    printf("File not found\n");
    
}

int main()
{
    int nob,blk_size,choice,loc=0;
    struct f list[20];
    printf("Enter no of blocks in KB: ");
    scanf("%d", &nob);
    printf("Enter blocksize in KB: ");
    scanf("%d", &blk_size);
    int disk[nob];
    l=nob;
    for(int i=0;i<nob;i++)
    disk[i]=0;

     while (1)
    {
        printf("\n File Operations \n");
        printf(" 1) Create\n");
        printf(" 2) Delete\n");
        printf(" 3) Print\n");
        printf(" 4) Exit\n");
        printf(" Enter Your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            
            case 1 :
                    {
                        loc++;
                        create(list,loc,blk_size,disk,nob);
                        
                        break;
                    }
            case 2 :
                    {
                        delete(list,loc,blk_size,disk,nob);
                        break;
                    }

            case 3 :
                    {
                        display(list,loc,blk_size,disk,nob);
                        break;
                    }

            case 4 :
                    {
                        printf(" Exit \n\n");
                        printf("\n\n The End \n\n");
                        exit(0);
                    }

            default :
                    {
                        printf(" Invalid Input!! \n\n");
                    }
        }
    }

    return 0;
}
