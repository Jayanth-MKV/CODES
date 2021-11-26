#include<stdio.h>
#include<stdlib.h>
#define htsize 10

struct node{
    int key;
    struct node *next;
};

struct node *ht[htsize];


int hash(int key){
    return key%htsize;
}

void insert(int k){
    struct node *temp,*current;
    int c=0;
    int i=hash(k);
    current=(struct node *)malloc(sizeof(struct node));
    current->link=NULL;
    current->key=k;
    if (find(key)==-1)
    {

    if(ht[i]==NULL){
        ht[i]=current;
        printf("Key Inserted\n");
    }
    else{
         temp = ht[a];
        while (temp->next!=NULL)
        {
            temp=temp->next;
        }
        last->next=current;
        printf("the key is inserted\n");

    // for(last=ht[i];last->key!=k && last->link!=NULL;last=last->link){
    //     c++;
    //     }
    // if(last->key==k){
    //         printf("Element is found at %d position in %dth index\n",c,i);
    //         printf("I am sorry you can't insert that element\n");
    //     }
    // else{
    //     last=ht[i];
    //     while(last->link!=NULL){
    //         last=last->link;
    //     }
    //     last->link=newnode;
    //     printf("the key is inserted\n");
    //     }
    }
    }
}

int find(int key){
    struct node *temp;
    int a;
    int index =0;
    a=hash(key);
    if(ht[a]==NULL){
        return -1;
    }
    else{
        temp = ht[a];
        while (temp->key!=key&&temp->next!=NULL)
        {
            index++;
            temp=temp->next;
        }
        if (temp->key==key)
        {
            printf("Element Found at Index no. : %d , At %d Position \n",index,a);
            return index; 
        }
        else{
            return -1;
        }
        
        
    }


    // else{
    //     for(find=ht[i];find->key!=ele && find->link!=NULL;find=find->link){
    //         c++;
    //     }
    //     if(find->key==ele){
    //         printf("element found at %d position in %dth index\n",c,i);
    //         return i;
    //     }
    //     else{
    //         printf("element not found\n");
    //         return-1;
    //     }
    // }
}

void delete(int key){
    struct node *prev=NULL;
    struct node *temp=NULL;
    int a=hash(key);
    int index=find(key);
    if(i!=-1){
        temp=ht[a];
        if (index==0)
        {
            free(temp);
            ht[i]=NULL;
            printf("The Element is Deleted\n");
        }
        else{
        while (index!=0)
        {   
            prev=temp;
            temp=temp->next;
            index--;
        }
        prev->next=temp->next;
        free(temp);
        printf("The Element is Deleted\n");
        }


        // for(find=ht[i];find->key!=k;find=find->link){
        //     prev=find;
        //     c++;
        // }
        // if(c==0){
        //     free(find);
        //     ht[i]=NULL;
        //     printf("the element is deleted\n");
        // }
        // else{
        //     temp=find->link;
        //     free(find);
        //     prev->link=temp;
        //     printf("\nthe element is deleted\n");
        // }
    }
}

void display(){
    struct node *m;
    // int x=100*htsize;
    int i;
    // int a[x][htsize];
    printf("The List of Elements is\n");
    for(i=0;i<htsize;i++){
        printf("%d",i);
        for(m=ht[i];m!=NULL;m=m->next){
            printf("%4d",m->key);
        }
        printf("\n");
    }
}

int main(){
    int c,key,i;
    for(i=0;i<htsize;i++){
        ht[i]=NULL;
    }
    printf("OPEN HASHING\n");
    printf("Enter A Option From One Of The Them\n");
    while(1){
        printf("1.Insert\n");
        printf("2.Delete\n");
        printf("3.Find\n");
        printf("4.Display\n");
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
            case 3: printf("Enter the element to find :\n");
                    scanf("%d",&key);
                    int a=find(key);
                    printf("\n");
                    break;
            case 4: display();
                    break;
            default:exit(1);
        }
    }
    return 0;
}