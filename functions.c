#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

// adding a brother
DoubleLinkedList* insert_DoubleLinkedList(DoubleLinkedList* doubleLinkedList, Node* node){
    DoubleLinkedList *new = (DoubleLinkedList *) malloc(sizeof(struct reg));
    new->node = node;

    if (doubleLinkedList != NULL) {
        doubleLinkedList->previous = new;
    }

    new->next = doubleLinkedList;
    new->previous = NULL;

    return new;
}

Node *searchById_FirstOrDefault(DoubleLinkedList *tree, int id) {
    Node * res;
    if(tree == NULL){
        return NULL;
    }

    if(tree->node->id == id){
        return tree->node;
    } else{
        DoubleLinkedList* temp = tree->next;
        while (temp != NULL){
            if(temp->node->id == id){
                return temp->node;
            } else {
                res = searchById_FirstOrDefault(temp->node->children, id);
                temp = temp->next;
                if (res != NULL) {
                    return (res);
                }
            }
        }

        res = searchById_FirstOrDefault(tree->node->children, id);
        return(res);
    }
}

int isUnique(LinkedList* list, char value[10]){
    if(list == NULL) {
        return 1;
    } else if(strcmp(list->code, value) == 0) {
        return 0;
    } else{
        isUnique(list->next, value);
    }
}

LinkedList* insert_LinkedList(LinkedList* list, Node* node){
//    if(isUnique(list, node->code)){
        LinkedList* new = malloc(sizeof(struct res));
        new->id = node->id;
        strcpy(new->code, node->code);
        strcpy(new->designation, node->designation);
        new->price = node->price;
        if(node->parent != NULL){
            new->parent = node->parent->id;
        }
        new->next = list;

        return new;
//    } else {
//        return list;
//    }
}
LinkedList* insertDetailed_LinkedList(LinkedList* list, int id, char *code, char * designation, double price, int parentId){
    LinkedList* new = malloc(sizeof(struct res));
    strcpy(new->code, code);
    strcpy(new->designation, designation);
    new->price = price;
    new->id = id;
    new->parent = parentId;
    new->next = list;

    return new;
}

LinkedList* searchByCode(DoubleLinkedList* tree, char *code, LinkedList* result){
    if(tree != NULL) {
        if (strcmp(tree->node->code, code) == 0) {
            result = insert_LinkedList(result, tree->node);

            searchByCode(tree->node->children, code, result);
        } else{
            DoubleLinkedList *temp = tree->next;
            while (temp != NULL) {
                if (strcmp(temp->node->code, code) == 0) {
                    result = insert_LinkedList(result, temp->node);
                }

                result = searchByCode(temp->node->children, code, result);

                temp = temp->next;
            }

            result = searchByCode(tree->node->children, code, result);
        }
    } else {
        return result;
    }
}
LinkedList* searchByDesignation(DoubleLinkedList *tree, char *designation, LinkedList* result) {
    if(tree != NULL) {
        if (strcmp(tree->node->designation, designation) == 0) {
            result = insert_LinkedList(result, tree->node);

            result = searchByDesignation(tree->node->children, designation, result);
        }

        DoubleLinkedList *temp = tree->next;
        while (temp != NULL) {
            if (strcmp(temp->node->designation, designation) == 0) {
                result = insert_LinkedList(result, temp->node);
            }

            result = searchByDesignation(temp->node->children, designation, result);
            temp = temp->next;
        }

        result = searchByDesignation(tree->node->children, designation, result);
    } else {
        return result;
    }
}

LinkedList* exportToLinkedList(DoubleLinkedList *tree, LinkedList* result){
    if(tree != NULL){
        Node* temp = tree->node;
        result = insert_LinkedList(result, temp);

        DoubleLinkedList *temp2 = tree->next;
        while (temp2 != NULL) {
            result = insert_LinkedList(result, temp2->node);
            result = exportToLinkedList(temp2->node->children, result);
            temp2 = temp2->next;
        }

        result = exportToLinkedList(tree->node->children, result);
    } else {
        return result;
    }
}

void swap(LinkedList *a, LinkedList *b) {
    int id = a->id;
    a->id = b->id;
    b->id = id;

    char *code = malloc(sizeof(char) * 10);
    strcpy(code,a->code);
    strcpy(a->code,b->code);
    strcpy(b->code,code);

    char *designation = malloc(sizeof(char) * 10);
    strcpy(designation,a->designation);
    strcpy(a->designation,b->designation);
    strcpy(b->designation,designation);

    double price = a->price;
    a->price = b->price;
    b->price = price;

    int parent = a->parent;
    a->parent = b->parent;
    b->parent = parent;
}
LinkedList *sortByCode_LinkedList(LinkedList* linkedList){
    int isSwapped;
    LinkedList* ptr;
    LinkedList* lastPtr = NULL;

    if(linkedList == NULL) {
        return NULL;
    }

    do {
        isSwapped = 0;

        ptr = linkedList;
        while (ptr->next != lastPtr) {
            if (strcmp(ptr->code, ptr->next->code) > 0) {
                swap(ptr, ptr->next);
                isSwapped = 1;
            }

            ptr = ptr->next;
        }

        lastPtr = ptr;
    } while (isSwapped);

    return linkedList;
}
LinkedList* sortByIdAsc_LinkedList(LinkedList* linkedList){
    int isSwapped;
    LinkedList* ptr;
    LinkedList* lastPtr = NULL;

    if(linkedList == NULL) {
        return NULL;
    }

    do {
        isSwapped = 0;

        ptr = linkedList;
        while (ptr->next != lastPtr) {
            if (ptr->id > ptr->next->id) {
                swap(ptr, ptr->next);
                isSwapped = 1;
            }

            ptr = ptr->next;
        }

        lastPtr = ptr;
    } while (isSwapped);

    return linkedList;
}

void destroy(LinkedList* head) {
    LinkedList* tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
int length(LinkedList* ptr){
    if (ptr == NULL){
        return 0;
    } else {
        int counter = 0;
        while (ptr != NULL) {
            counter++;
            ptr = ptr->next;
        }

        return counter;
    }
}
void print_LinkedList(LinkedList* ptr) {
    int counter = 1;
    while (ptr != NULL) {
        printf("%d. [%d] %s - %s\n", counter, ptr->id, ptr->code, ptr->designation);

        counter++;
        ptr = ptr->next;
    }
}
void printDetailed_LinkedList(LinkedList* ptr){
    int counter = 1;
    while (ptr != NULL) {
        printf("%d. [%s] %s - %.2f\n", counter, ptr->code, ptr->designation, ptr->price);

        counter++;
        ptr = ptr->next;
    }
}
void printTree(DoubleLinkedList *tree){
    if(tree != NULL){
        Node* temp = tree->node;
        printf("{%s-", temp->code);

        DoubleLinkedList *temp2 = tree->next;
        while (temp2 != NULL) {
            printf("%s-", temp2->node->code);
            printTree(temp2->node->children);
            temp2 = temp2->next;
        }

        printTree(tree->node->children);
        printf("}");
    }
}

void printComponent(Node* node){
    printf("1. Code: %s\n", node->code);
    printf("2. Designation: %s\n", node->designation);
    printf("3. Price: %.2f\n", node->price);
}

int removeElement(DoubleLinkedList* tree, int id) {
    int isRemoved = 0;
    if(tree == NULL){
        return 0;
    }

    if(tree->node->id == id){
        if(tree->previous != NULL) {
            tree->previous->next = NULL;
        } else{
            tree->node->parent->children = tree->next;
        }

        if(tree->next != NULL) {
            tree->next->previous = tree->previous;
        }


        free(tree);
        tree = NULL;

        return 1;
    } else{
        DoubleLinkedList* temp = tree->next;
        while (temp != NULL){
            if(temp->node->id == id){
                if(temp->previous != NULL) {
                    temp->previous->next = NULL;
                }else{
                    temp->node->parent->children = temp->next;
                }

                if(temp->next != NULL) {
                    temp->next->previous = temp->previous;
                }

                free(temp);
                temp = NULL;

                return 1;
            } else {
                isRemoved = removeElement(temp->node->children, id);
                temp = temp->next;
                if (isRemoved != 0) {
                    return (isRemoved);
                }
            }
        }

        isRemoved = removeElement(tree->node->children, id);
        return(isRemoved);
    }
}

DoubleLinkedList* extractComponent(DoubleLinkedList* tree, int id){
    DoubleLinkedList* set = NULL;
    if(tree == NULL){
        return 0;
    }

    if(tree->node->id == id){
        if(tree->previous != NULL) {
            tree->previous->next = NULL;
        } else{
            tree->node->parent->children = tree->next;
        }

        if(tree->next != NULL) {
            tree->next->previous = tree->previous;
            if(tree->previous != NULL) {
                tree->previous->next = tree->next;
            }
        }

        DoubleLinkedList* temp2 = tree;
        while (temp2 != NULL){
            temp2->node->parent = NULL;

            temp2 = temp2->next;
        }

        tree->previous = NULL;
        tree->next = NULL;

        return tree;
    } else{
        DoubleLinkedList* temp = tree->next;
        while (temp != NULL){
            if(temp->node->id == id){
                if(temp->previous != NULL) {
                    temp->previous->next = NULL;
                }else{
                    temp->node->parent->children = temp->next;
                }

                if(temp->next != NULL) {
                    temp->next->previous = temp->previous;
                    if(temp->previous != NULL) {
                        temp->previous->next = temp->next;
                    }
                }

                DoubleLinkedList* temp2 = temp;
                while (temp2 != NULL){
                    temp2->node->parent = NULL;

                    temp2 = temp2->next;
                }

                temp->previous = NULL;
                temp->next = NULL;

                return temp;
            } else {
                set = extractComponent(temp->node->children, id);

                temp = temp->next;

                if (set != 0) {
                    return (set);
                }
            }
        }

        set = extractComponent(tree->node->children, id);
        return (set);
    }
}

void calculateCost(DoubleLinkedList* tree, double *cost){
    if(tree != NULL){
        Node* temp = tree->node;
        (*cost) = (*cost + temp->price);

        DoubleLinkedList *temp2 = tree->next;
        while (temp2 != NULL) {
            (*cost) = (*cost + temp2->node->price);
            calculateCost(temp2->node->children, cost);
            temp2 = temp2->next;
        }

        calculateCost(tree->node->children, cost);
    }
}

LinkedList* invertList(LinkedList* list){
    LinkedList* reg = NULL;

    LinkedList* temp = list;
    while(temp!=NULL){
        reg = insertDetailed_LinkedList(reg, temp->id, temp->code, temp->designation, temp->price, temp->parent);
        temp = temp->next;
    }

    return reg;
}
void appendFile(Node* node){
    FILE* file = fopen("equipment.txt", "a");
    fprintf(file, "%d|%s|%s|%.2f", node->id, node->code, node->designation, node->price);
    if(node->parent != NULL){
        fprintf(file, "|%d\n", node->parent->id);
    } else{
        fprintf(file, "|0\n");
    }

    fclose(file);
}
void writeFile(LinkedList* elements){
    FILE* file = fopen("equipment.txt", "w");
    LinkedList* temp = elements;
    while (temp != NULL){
        fprintf(file, "%d|%s|%s|%.2f|%d\n", temp->id, temp->code, temp->designation, temp->price, temp->parent);

        temp = temp->next;
    }

    fclose(file);
}
void updateFile(Node* node){
    FILE* file = fopen("equipment.txt", "r");
    LinkedList* data = NULL;

    int id;
    char code[10];
    char designation[10];
    double price;
    int parentId;
    while (fscanf(file, "%d|%[^|]|%[^|]|%lf|%d", &id, code, designation, &price, &parentId) > 0){
        if(id == node->id){
            if(node->parent != NULL) {
                data = insertDetailed_LinkedList(data, node->id, node->code, node->designation, node->price, node->parent->id);
            } else {
                data = insertDetailed_LinkedList(data, node->id, node->code, node->designation, node->price, 0);
            }
        } else{
            data = insertDetailed_LinkedList(data, id, code, designation, price, parentId);
        }
    }

    fclose(file);

    data = invertList(data);
    writeFile(data);
}






DoubleLinkedList* addComponentCommand(DoubleLinkedList* tree){
    int attachTo;
    char code[10];
    char designation[10];
    double price;

    if(tree != NULL){
        printf("Attach to: ");
        scanf("%d", &attachTo);
    }
    printf("New component details: \n");
    printf("Code: ");
    scanf("%s", code);
    printf("Designation: ");
    scanf("%s", designation);
    printf("Price: ");
    scanf("%lf", &price);

    Node* node = createNode(code, designation, price);
    if (tree == NULL) {
        tree = insert_Tree(tree, node, NULL);
    } else {
        tree = insert_Tree(tree, node, attachTo);
    }

    return tree;
}
void searchByDesignationCommand(DoubleLinkedList* tree){
    char designation[10];
    printf("Designation: ");
    scanf("%s[^\t\000\n]%*c", designation);

    LinkedList* result = NULL;
    result = searchByDesignation(tree, designation, result);
    print_LinkedList(result);
    printf("%d results were found.\n", length(result));
}
void searchByCodeCommand(DoubleLinkedList* tree){
    char code[10];
    printf("Code: ");
    scanf("%s[^\t\000\n]%*c", code);

    LinkedList* result = NULL;
    result = searchByCode(tree, code, result);
    printDetailed_LinkedList(result);
}
void listComponentsCommand(DoubleLinkedList* tree){
    LinkedList* result = NULL;
    result = exportToLinkedList(tree, result);
    sortByCode_LinkedList(result);
    print_LinkedList(result);
}
DoubleLinkedList* editComponentCommand(DoubleLinkedList* tree){
    int id;
    printf("Id: ");
    scanf("%d", &id);

    Node* node = searchById_FirstOrDefault(tree, id);

    if(node == NULL) {
        printf("No such component found.\n");
        return tree;
    }

    printComponent(node);

    printf("Which field do you want to edit? \n");
    int field;
    scanf("%d", &field);

    char newCode[10];
    char newDesignation[10];
    double newPrice;
    switch (field){
        case 1:
            printf("Code: ");
            scanf("%s[^\t\000\n]%*c", newCode);
            strcpy(node->code, newCode);
            break;
        case 2:
            printf("Designation: ");
            scanf("%s[^\t\000\n]%*c", newDesignation);
            strcpy(node->designation, newDesignation);
            break;
        case 3:
            printf("Price: ");
            scanf("%lf", &newPrice);
            node->price = newPrice;
            break;
        default:
            printf("No such field.\n");
            break;
    }

    updateFile(node);

    return tree;
}
DoubleLinkedList* removeComponentCommand(DoubleLinkedList* tree){
    int id;
    printf("Id: ");
    scanf("%d", &id);

    int removed = removeElement(tree, id);
    if (removed == 1) {
        printf("The element with ID %d is successfully removed.\n", id);
    } else{
        printf("Not found.\n");
    }

    LinkedList* result = NULL;
    result = exportToLinkedList(tree, result);
    sortByIdAsc_LinkedList(result);
    writeFile(result);

    return tree;
}
DoubleLinkedList* setComponentCommand(DoubleLinkedList* tree){
    int id;
    printf("Id: ");
    scanf("%d", &id);

    int attachTo;
    printf("Attach to: ");
    scanf("%d", &attachTo);

    DoubleLinkedList* set = extractComponent(tree, id);
    if (set == NULL) {
        printf("Not found.\n");
    } else{
        insert_Tree(tree, set->node, attachTo);
        printf("The element with ID %d is successfully set.\n", id);
    }

    LinkedList* result = NULL;
    result = exportToLinkedList(tree, result);
    sortByIdAsc_LinkedList(result);
    writeFile(result);

    return tree;
}
void printTreeCommand(DoubleLinkedList* tree){
    printTree(tree);
    printf("\n");
}
void calculateCostCommand(DoubleLinkedList* tree){
    LinkedList* result = NULL;
    result = exportToLinkedList(tree, result);
    printDetailed_LinkedList(result);

    double cost = 0;
    calculateCost(tree, &cost);
    printf("Total cost: %.2f\n", cost);
}