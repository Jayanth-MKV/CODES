#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct f{
char name[10];
int size;
int start;
int no_blks;
int active;
};

bool allocate(struct f list[],int st,int blks,int disk[],int nob){
if(st+blks>nob){
    return false;
}
int emp=1,i;

for(i=st;i<blks+st;i++){
    if(disk[i]==0){
        continue;
    }
    else{
        return false;
    }
}

for(i=st;i<blks+st;i++)
disk[i]=1;

return true;

}

void create(struct f list[],int loc,int blk_size,int disk[],int nob){
    char fn[10];
    int fs,blks,st=-1;
   
        printf("Enter the file name: ");
        scanf("%s",fn);
        printf("Enter the size of the file: ");
        scanf("%d",&fs);
        blks=(fs/blk_size)+((fs%blk_size==0)?0:1);
	int flag=0;
	for(int i=0;i<nob;i++){
	flag=0;
	if(disk[i]==0){
	for(int j=i;j<=i+blks;j++){
	if(disk[j]==0){
		flag=1;
		continue;
	}
	else{
		flag=0;
	break;
	}
	}
	if(flag==1){
		st=i;
		break;
	}
	i+=blks;
	}

	}

	printf("No of blocks to allocate : %d\n",blks);
	
	if(st==-1){
	printf("Cant allocate memory for file\n");
	return;
	}
//        blks=(fs/blk_size)+((fs%blk_size==0)?0:1);

	//printf("No of blocks to allocate : %d\n",blks);

        if(allocate(list,st,blks,disk,nob)){
            list[loc-1].active=1;
            strcpy(list[loc-1].name,fn);
            list[loc-1].no_blks=blks;
            list[loc-1].start=st;
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
    for(int i=list[pos].start;i<list[pos].start+list[pos].no_blks;i++)
    disk[i]=0;
    list[pos].active=0;
    list[pos].no_blks=0;
    list[pos].start=0;
    list[pos].size=0;
    strcpy(list[pos].name,"");
    
    printf(" File deleted successfully\n");

}


}

void display(struct f list[],int loc,int blk_size,int disk[],int nob){

    printf("\n Files allocation Details \n");
    printf("Filename size start len(blks) seq\n");
    for(int i=0;i<loc;i++){
        if(list[i].active==1){
            printf("%s\t %d\t %d\t %d\t",list[i].name,list[i].size,list[i].start,list[i].no_blks);
            for(int j=list[i].start;j<list[i].start+list[i].no_blks;j++)
            printf("%d - ",j);
            printf("\n");
        }
    }

    printf("Free Disk Blocks \n");
    for(int i=0;i<nob;i++){
    if(disk[i]==0)
    printf("%d - ",i);
    }
    printf("\n");
    /*
    char name[10];
    printf("Enter the file name to display\n");
    scanf("%s",name);
    for(int i=0;i<loc;i++){
        if(!strcmp(name,list[i].name)){
        printf("----Filename - %s----\n",list[i].name);
        printf("Size : %d\n No_of_blocks : %d\nStart-block - %d\n",list[i].size,list[i].no_blks,list[i].start);
        return;
        }
    }
    printf("File not found\n");
    */
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
