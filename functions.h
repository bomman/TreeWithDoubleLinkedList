#ifndef TREEWITHLINKEDLIST_PRACTICALWORK_FUNCTIONS_H
#define TREEWITHLINKEDLIST_PRACTICALWORK_FUNCTIONS_H

typedef struct node {
    int id;
    char code[10];
    char designation[10];
    double price;

    struct reg* children;
    struct node* parent;
} Node;

typedef struct reg {
    Node * node;

    struct reg *next;
    struct reg *previous;
} DoubleLinkedList;

typedef struct res {
    int id;
    char code[10];
    char designation[10];
    double price;
    int parent;

    struct res *next;
} LinkedList;

DoubleLinkedList* insert_DoubleLinkedList(DoubleLinkedList* doubleLinkedList, Node* node);
Node *searchById_FirstOrDefault(DoubleLinkedList *tree, int id);
void appendFile(Node* node);

// Commands
DoubleLinkedList* addComponentCommand(DoubleLinkedList* tree);
void searchByDesignationCommand(DoubleLinkedList* tree);
void searchByCodeCommand(DoubleLinkedList* tree);
void listComponentsCommand(DoubleLinkedList* tree);
DoubleLinkedList* editComponentCommand(DoubleLinkedList* tree);
DoubleLinkedList* removeComponentCommand(DoubleLinkedList* tree);
DoubleLinkedList* setComponentCommand(DoubleLinkedList* tree);
void printTreeCommand(DoubleLinkedList* tree);
void calculateCostCommand(DoubleLinkedList* tree);

#endif //TREEWITHLINKEDLIST_PRACTICALWORK_N_H

