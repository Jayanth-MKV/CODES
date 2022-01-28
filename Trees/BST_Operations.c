#include<stdio.h>
#include<stdlib.h>

struct node{
        int data;
        struct node* left;
        struct node* right;
};

void inorder(struct node*);
int search(struct node* root,int val);

struct node* create_node(){
        struct node* n_new =(struct node*)malloc(sizeof(struct node));
        n_new->data=-1;
        n_new->left=NULL;
        n_new->right=NULL;
        return n_new;
}

void insert(struct node* root,int val){

        struct node* n_new=create_node();
        n_new->data=val;
        if(root->data==-1){
                root->data=val;
                return;
        }
        if(root==NULL){
                root=n_new;
                root->data=val;
                return;
        }

        int res=search(root,val);
        if(res==1){
                printf("The value is already present\n");
        }
        else{
        struct node* prev=NULL;
        struct node* curr=root;

        while(curr!=NULL){
                prev=curr;
                if(val<curr->data){
                        curr=curr->left;
                }
                else if(val>curr->data){
                        curr=curr->right;
                }
 if(val<prev->data){
                prev->left=n_new;
                return;
        }

        prev->right=n_new;
}

}
}

int search(struct node* root , int val){

        if(root==NULL){
        return -1;
        }
        if(val==root->data){
        printf("Element Found\n");
        return 1;
        }
        if(val< root->data){
        search(root->left,val);
        }
        else{
        search(root->right,val);
        }
}


struct node* minVal(struct node* root){
        struct node* temp=root;
        while(temp && temp->left!=NULL){
                temp=temp->left;
        }
        return temp;
}



void del(struct node* root,int val){

        if(root==NULL)
                return;
        if(search(root,val)==-1){
                printf("Value not Found");
                return;
        }

        struct node* curr=root;
        struct node* prev=NULL;

        while(curr!=NULL){
 if(curr->data==val)
                        break;
                if(val<curr->data){
                        prev=curr;
                        curr=curr->left;
                }
                else if(val>curr->data){
                        prev=curr;
                        curr=curr->right;
                }

        }

         if (curr->left==NULL && curr->right==NULL){
         if(val<prev->data){
                prev->left=NULL;
                free(curr);
                return;
        }
        prev->right=NULL;
         }
        else if(curr->left == NULL){
        prev->left=curr->left;
        free(curr);
        return;
        }
        else if(curr->right == NULL){
        prev->right=curr->right;
        free(curr);
        return;
        }
         else{

         struct node* temp=minVal(curr->right);
         int a=temp->data;
         del(root,temp->data);
         curr->data=a;

         }




}


int main(){
        struct node* tree1=create_node();
        insert(tree1,10);
        insert(tree1,30);
        insert(tree1,40);
		insert(tree1,20);
        insert(tree1,60);
        insert(tree1,50);
        printf("The tree1 contains \n");
        inorder(tree1);
        del(tree1,10);
        printf("\n");
        inorder(tree1);
        return 0;
}



void  inorder(struct node* root){
		if(root==NULL){
        return;
		}
        inorder(root->left);
        printf("%d \n",root->data);
        inorder(root->right);
}