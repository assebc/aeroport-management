#include <stdio.h>
#include <stdlib.h>

typedef struct btree node;

void insert(node ** tree, int val);
void searchfor(int val, node ** tree);
void print_preorder(node * tree);
int count_nodes(node *tree);