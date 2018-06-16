#include "functions.h"

#ifndef TREEWITHLINKEDLIST_PRACTICALWORK_ENGINE_H
#define TREEWITHLINKEDLIST_PRACTICALWORK_ENGINE_H

void run(DoubleLinkedList* tree);

Node* createNode(char code[10], char designation[10], double price);
DoubleLinkedList* insert_Tree(DoubleLinkedList* tree, Node* node, int attachTo);

#endif //TREEWITHLINKEDLIST_PRACTICALWORK_N_H

