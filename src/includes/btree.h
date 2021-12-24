#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct btree btree;

btree * create_node(int value);
void insertID(btree ** rootptr, int val);
bool findID(btree * root, int value);
btree * id_wanted(btree * root, int value);
int id_wanted2(btree * root, int value);
void insert_person(btree * rootptr, int id_repo);