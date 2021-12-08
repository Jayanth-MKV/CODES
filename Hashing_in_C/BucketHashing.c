#include<stdio.h>
#include<stdlib.h>
#define htsize 10
#define noofbuk 5
#define buksize htsize/noofbuk
int overflow_index=0;

int array[noofbuk][buksize];
int overflow[10];

int hash(int key){
    return key%noofbuk;
}

void insert(int key){
	int i,j;
     int a=hash(key);
	for(i=0;i<noofbuk;i++){
    for(j=0;j<buksize;j++){
	if(array[a][j]==-1){
		array[a][j]=key;
		return;
	}
	else if(array[a][j]==key){
		printf("Element already exists\n");
		return;
	}
}

for(int k=0;k<overflow_index;k++){
    if(overflow[k]==-1){
    overflow[k]=key;
        return;
    }
}
    
if (overflow_index<10)
{
overflow[overflow_index++]=key;
break;
}
else{
printf("HASHTABLE IS FULL\n");
break;
}
}

}

void delete(int key){
	int i,j;
    int a=hash(key);
	for(i=0;i<noofbuk;i++){  
    for(j=0;j<buksize;j++){
	if(array[a][j]==key){
		array[a][j]=-1;
		return;
	}
	}

    for(int k=0;k<overflow_index;k++){
    if(overflow[k]==key){
        overflow[k]=-1;
        return;
    }
    }
}
printf("Element not found\n");
}
	
void search(int key){
	int b=0;
	int i,j;
    int a=hash(key);
	for(i=0;i<noofbuk;i++){
    for(j=0;j<buksize;j++){
	if(array[a][j]==key){
		printf("Element found at position : %d \n",a);
		return;
	}
	}   
}
for(int k=0;k<overflow_index;k++){
    if(overflow[k]==key){
        printf("Element found at position : %d in overflow array \n",k);
        return;
    }
    }
printf("Element not found\n");
}

void display(){
		int i,j;
        int b=0;
		for(i=0;i<noofbuk;i++){
        for(j=0;j<buksize;j++){
		printf("%d : ",i);
		if(array[i][j]!=-1){
		printf("%d \n",array[i][j]);
		}
		else{
		printf("\n");
		}
		}
}
printf("\n");
printf("Overflow Bucket\n");
for(int k=0;k<10;k++){
    printf("%d : ",k);
		if(overflow[k]!=-1){
		printf("%d \n",overflow[k]);
		}
		else{
		printf("\n");
		}
}

}



int main(){
    int c,key,i;
    for(i=0;i<10;i++){
        overflow[i]=-1;
    }

    int j;
		for(i=0;i<noofbuk;i++){
        for(j=0;j<buksize;j++){
            array[i][j]=-1;
        }
        }


    printf("BUCKET HASHING\n");
    printf("Enter an Option\n");
    printf("1.Insert\n");
    printf("2.Delete\n");
    printf("3.Find\n");
    printf("4.Display\n");
    printf("5.Enter any number to exit\n");
    while(1){
        printf("Enter an Option\n");
        scanf("%d",&c);
        switch(c){
            case 1: printf("Enter the key to insert : \n");
                    scanf("%d",&key);
                    insert(key);
                    break;
            case 2: printf("Enter the key to delete :\n");
                    scanf("%d",&key);
                    delete(key);
                    break;
            case 3: printf("Enter the key to find :\n");
                    scanf("%d",&key);
                    search(key);
                    printf("\n");
                    break;
            case 4: display();
                    break;
            default:exit(1);
        }
    }
    return 0;
}