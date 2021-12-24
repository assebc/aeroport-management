#include <stdio.h>
#include <stdlib.h>

struct btree {
    int data;
    int data2;
    struct btree * left;
    struct btree * right;    
};

typedef struct btree node;

void insert(node ** tree, int val){
    
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        temp->data2 = 0;
        *tree = temp;
        if (temp->data == val) temp->data2 += 1;
        return;
    }

    if(val < (*tree)->data) insert(&(*tree)->left, val);
    else if(val > (*tree)->data) insert(&(*tree)->right, val);
    else insert(&(*tree), val);

}

void searchfor(int val, node ** tree){
    
    node ** temp = tree;
    
    while((*temp)->data!=val){
         if ((*temp)->data<val) searchfor(val, &(*temp)->left);
         else searchfor(val,&(*temp)->right);
    }

}


void print_preorder(node * tree){
  
    if(tree)
    {
        printf("%d\n",tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }

}

int count_nodes(node *tree){

    static int count = 0;
    if(tree){
        count_nodes(tree->left);
        count++;
        count_nodes(tree->right);
    }
    return count;
}
