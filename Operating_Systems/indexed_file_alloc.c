#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct f{

char name[10];
int size;
int no_blks;
int active;
int index;
};


struct d{
    int a[20];
    int a_lim;
    int lim;
    int active;
};

int l;

int ind_alloc(struct d disk[],int nob){
int flag=-1,ind,cnt=0;    
while(cnt<nob){  
    ind=rand()%nob;
    int ac=disk[ind].active;
    if(ac==0){
    flag=ind;
    break;
    }
    cnt++;
}
return flag;
}

bool allocate(struct f list[],int loc,int blks,struct d disk[],int nob){
int i,cnt=0;
int ind=ind_alloc(disk,nob);   // index block allocation
if(ind==-1)
return false;
else{
disk[ind].active=1;
list[loc-1].index=ind;
l--;
}

if(l<blks){ // no sufficient blocks
    return false;
}
while(cnt<blks){
    int r=rand()%nob;
    if(disk[r].active==0){
    if(disk[ind].a_lim!=(disk[ind].lim)-1){
        
    disk[ind].a[(disk[ind].a_lim)]=r;
    printf("index-%d %d\n",ind,disk[ind].a[(disk[ind].a_lim)]);
    disk[r].active=1;
    disk[ind].a_lim+=1;
    cnt++;
    l--;
    }

    if(disk[ind].a_lim==disk[ind].lim-1 && cnt<blks){
        int p=ind_alloc(disk,nob);
        if(p==-1){
            return false;
        }
        disk[ind].a[(disk[ind].lim)-1]=p;
        ind=p;
        disk[ind].active=1;
        l--;
    }
    }
}

return true;

}

void create(struct f list[],int loc,int blk_size,struct d disk[],int nob){
    
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

int search(struct f list[],int loc,int blk_size,struct d disk[],int nob){

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

void delete(struct f list[],int loc,int blk_size,struct d disk[],int nob){
int pos=search(list,loc,blk_size,disk,nob);
if(pos==-1){
    printf("File not found");
    return;
}
else{
    int ind=list[pos].index;
    // deleting memory of index block
    while(1){
        disk[ind].active=0;
        l++;
        for(int i=0;i<blk_size-1;i++){
            disk[ind].a[i]=-1;
        }
        if(disk[ind].a[blk_size-1]!=-1){
            ind=disk[ind].a[blk_size-1];
            disk[ind].a[blk_size-1]=-1;
        }
        else{
            break;
        }
    }
    
    l+=list[pos].no_blks;
    list[pos].active=0;
    list[pos].no_blks=0;
    list[pos].size=0;
    list[pos].index=0;
    strcpy(list[pos].name,"");
    
    printf(" File deleted successfully\n");

}


}

void display(struct f list[],int loc,int blk_size,struct d disk[],int nob){

    printf("\n Files allocation Details \n");
    printf("Filename size index len_blks seq\n");
    for(int i=0;i<loc;i++){
        if(list[i].active==1){
        printf("%s\t %d\t %d\t %d\t ",list[i].name,list[i].size,list[i].index,list[i].no_blks);
        int ind=list[i].index,cnt=0,blks=list[i].no_blks;
        while(cnt<blks){
        
        for(int i=0;i<blk_size-1;i++){
            if(disk[ind].a[i]!=-1)
            printf("%d-",disk[ind].a[i]);
            cnt++;
        }
        if(disk[ind].a[blk_size-1]!=-1){
            printf("%d-",disk[ind].a[blk_size-1]);
            ind=disk[ind].a[blk_size-1];
            cnt++;
        }
        else{
            break;
        }

        }
            printf("\n");
        }
    }

    printf(" Disk FREE \n");
    for(int i=0;i<nob;i++){
    if(disk[i].active==0)
    printf("%d - ",i);
    }
    printf("\n");
}

int main()
{
    int nob,blk_size,choice,loc=0;
    struct f list[20];
    printf("Enter no of blocks in KB: ");
    scanf("%d", &nob);
    printf("Enter blocksize in KB: ");
    scanf("%d", &blk_size);
    struct d disk[20];
    l=nob;
    for(int i=0;i<nob;i++){
    disk[i].lim=blk_size;
    disk[i].active=0;
    disk[i].a_lim=0;
    for (int j = 0; j < 20; j++)
    disk[i].a[j]=-1;
    }
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
                    //    print(disk,nob);
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
