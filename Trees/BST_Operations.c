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
        n_new->data=-111;
        n_new->left=NULL;
        n_new->right=NULL;
        return n_new;
}

void insert(struct node* root,int val){

        struct node* n_new=create_node();
        n_new->data=val;
        if(root->data==-111){
                root->data=val;
                return;
        }
        // if(root==NULL){
        //         root=n_new;
        //         root->data=val;
        //         return;
        // }

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
                
}

        if(val<prev->data){
                prev->left=n_new;
                return;
        }

        prev->right=n_new;

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



// void del(struct node** r,int val){
//         struct node* root=*r;
//         if(root==NULL)
//                 return;
//         if(search(root,val)==-1){
//                 printf("Value not Found");
//                 return;
//         }

//         struct node* curr=root;
//         struct node* prev=NULL;

//         while(curr!=NULL){
//                 if(curr->data==val)
//                         break;
//                 if(val<curr->data){
//                         prev=curr;
//                         curr=curr->left;
//                 }
//                 else if(val>curr->data){
//                         prev=curr;
//                         curr=curr->right;
//                 }

//         }

//          if (curr->left==NULL && curr->right==NULL){
//          if(val<prev->data){
//                 prev->left=NULL;
//                 free(curr);
//                 return;
//         }
//         prev->right=NULL;
//         }
//         else if(curr->left == NULL){
//                 if (curr==root)
//                 {       printf("hii");
//                         **r=*(root->right);
//                         return;
//                 }
                
//         prev->left=curr->left;
//         free(curr);
//         return;
//         }
//         else if(curr->right == NULL){
//         prev->right=curr->right;
//         free(curr);
//         return;
//         }
//          else{

//          struct node* temp=minVal(curr->right);
//          int a=temp->data;
//          del(r,temp->data);
//          curr->data=a;

//          }

// }



struct node* del(struct node *root, int data) {
  if (root == NULL) {
     return NULL;
  }
  if (data < root->data) {  
      root->left = del(root->left, data);
  } else if (data > root->data) { 
      root->right = del(root->right, data);
  } else {
     if (root->left == NULL && root->right == NULL) {
        free(root); 
        root = NULL;
     }
     else if (root->left == NULL) {
        struct node *temp = root; 
        root = root->right;
        free(temp);
     }
     
     else if (root->right == NULL) {
        struct node *temp = root;
        root = root->left;
        free(temp);
     }
     else {
        struct node *temp = minVal(root->right); 
        root->data = temp->data; 
        root->right = del(root->right, temp->data); 
     }
  }
  return root;
}



        // struct node* tree1=create_node();
        // insert(tree1,10);
        // insert(tree1,30);
        // insert(tree1,40);
	// insert(tree1,20);
        // insert(tree1,60);
        // insert(tree1,50);
        // printf("The tree1 contains \n");
        // inorder(tree1);
        // tree1=del(tree1,10);
        // printf("\n");
        // inorder(tree1);
        // return 0;

        int main(){
        struct node *root=create_node();
        int choice,k,res;

        while(1)
        {
                printf("\n");
                printf("1.Insert\n");
                printf("2.Delete\n");
                printf("3.Display\n");
                printf("4.Search\n");
                printf("5.Quit\n");
                printf("\nEnter your choice : ");
                scanf("%d",&choice);

                switch(choice)
                {

                case 1:
                        printf("Enter the key to be inserted : ");
                        scanf("%d",&k);
                        insert(root, k);
                        break;

                case 2:
                        printf("Enter the key to be deleted : ");
                        scanf("%d",&k);
                        root = del(root, k);
                        break;

                case 3:
                        printf("\n");
                        inorder(root);
                        printf("\n");
                        break;

                case 4:
                        printf("Enter the key to be searched : ");
                        scanf("%d",&k);
                        res = search(root, k);
                        if(res==1){
                                printf("The value is present\n");
                        }
                        else{
                                printf("The value is not Present\n");
                        }
                        break;
                        
                case 5:
                        exit(1);
                        
                default:
                        printf("Wrong choice\n");
                        
                }
        }
        
        return 0;



}



void  inorder(struct node* root){
	if(root==NULL){
                return;
		}
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
}
