#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

int counter = 0;

void printMenu() {
    printf("------- MENU -------\n");
    printf("1. Add component\n");
    printf("2. Search by component designation\n");
    printf("3. Search by component code\n");
    printf("4. List alphabetically the components\n");
    printf("5. Edit component\n");
    printf("6. Remove component\n");
    printf("7. Set component\n");
    printf("8. Consult equipment\n");
    printf("9. Calculate cost\n");
    printf("----- END MENU -----\n");
}

DoubleLinkedList* manageCommands(int command, DoubleLinkedList* mainTree){
    switch (command){
        case 1:
            mainTree = addComponentCommand(mainTree);
            break;
        case 2:
            searchByDesignationCommand(mainTree);
            break;
        case 3:
            searchByCodeCommand(mainTree);
            break;
        case 4:
            listComponentsCommand(mainTree);
            break;
        case 5:
            mainTree = editComponentCommand(mainTree);
            break;
        case 6:
            mainTree = removeComponentCommand(mainTree);
            break;
        case 7:
            mainTree = setComponentCommand(mainTree);
            break;
        case 8:
            printTreeCommand(mainTree);
            break;
        case 9:
            calculateCostCommand(mainTree);
            break;
        default:
            printf("Invalid command.\n");
            break;
    }

    return mainTree;
}

void run(DoubleLinkedList* newTree){
    setbuf(stdout, 0);
    printMenu();
    int command;
    while(1) {
        printf("Enter a command: ");
        scanf("%d", &command);

        if (command == -1){
            printf("Goodbye!");
            break;
        }

        newTree = manageCommands(command, newTree);
    }
}

Node* createNode(char code[10], char designation[10], double price){
    Node* newNode = malloc(sizeof(struct node));
    strcpy(newNode->code, code);
    strcpy(newNode->designation, designation);
    newNode->id = ++counter;
    newNode->price = price;
    newNode->children = NULL;
    newNode->parent = NULL;

    printf("Created node with ID %d\n", counter);
    return newNode;
}

DoubleLinkedList *searchParentById(DoubleLinkedList *tree, int id) {
    DoubleLinkedList * res;
    if(tree == NULL){
        return NULL;
    }

    if(tree->node->id == id){
        return tree;
    } else{
        DoubleLinkedList* temp = tree->next;
        while (temp != NULL){
            if(temp->node->id == id){
                return temp;
            } else {
                res = searchParentById(temp->node->children, id);
                temp = temp->next;
                if (res != NULL) {
                    return (res);
                }
            }
        }

        res = searchParentById(tree->node->children, id);
        return(res);
    }
}

// adding a child
DoubleLinkedList* insert_Tree(DoubleLinkedList* tree, Node* node, int attachTo){
    if(attachTo == NULL){
        DoubleLinkedList* new = malloc(sizeof(struct reg));
        new->node = node;
        new->next = NULL;
        new->previous = NULL;

        appendFile(node);

        return new;
    } else {
        Node* target = searchById_FirstOrDefault(tree, attachTo);
        if(target == NULL) {
            printf("The node to which you want to attach a new component cannot be found.\n");
        } else{
            target->children = insert_DoubleLinkedList(target->children, node);
            node->parent = target;

            // TODO: move to addComponentCommand
            appendFile(node);
        }

        return tree;
    }
}

