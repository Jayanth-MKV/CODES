#include<stdio.h>
#define htsize 10


int array[htsize];

int hash(int key,int i){
    return (key+i*i)%htsize;
}

void insert(int key){
	int i=0;
	for(i=0;i<htsize;i++){
	int a=hash(key,i);
	if(array[a]==-1){
		array[a]=key;
		return;
	}
	else if(array[a]==key){
		printf("Element already exists\n");
		return;
	}
}
printf("HASHTABLE IS FULL\n");
}

void delete(int key){
	int i=0;
	for(i=0;i<htsize;i++){
	int a=hash(key,i);
	if(array[a]==key){
		array[a]=-1;
		return;
	}
	}
	printf("Element not found\n");
}
	
void search(int key){
	int i;
	for(i=0;i<htsize;i++){
	int a=hash(key,i);
	if(array[a]==key){
		printf("Element found at position : %d \n",a);
		return;
	}
	}
	printf("Element not found\n");
}

void display(){
		int i;
		for(i=0;i<htsize;i++){
		printf("%d : ",i);
		if(array[i]!=-1){
		printf("%d \n",array[i]);
		}
		else{
		printf("\n");
		}
		}
}



int main(){
    int c,key,i;
    for(i=0;i<htsize;i++){
        array[i]=-1;
    }
    printf("CLOSED HASHING\n");
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
