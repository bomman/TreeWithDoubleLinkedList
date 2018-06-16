#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "engine.h"

void main(){
    fclose(fopen("equipment.txt", "w"));
    Node* laptop = createNode("Asus", "laptop", 1000);
    Node* video = createNode("Nvidia", "videocard", 200);
    Node* hard = createNode("Samsung", "HDD", 100);
    Node* processor = createNode("Intel", "CPU", 200);
    Node* platter = createNode("Platter", "HDD", 2);
    Node* head = createNode("RWHead", "HDD", 3);
    Node* actuator = createNode("Actuator", "HDD", 0.2);
    Node* headArm = createNode("HeadArm", "RWHead", 0.2);
    Node* slider = createNode("Slider", "RWHead", 0.22);
    Node* rwElement = createNode("RWElement", "RWHead", 0.22);
    Node* leadWires = createNode("LeadWires", "RWHead", 0.22);

    DoubleLinkedList *tree = NULL;
    tree = insert_Tree(tree, laptop, NULL);
    tree = insert_Tree(tree, video, 1);
    tree = insert_Tree(tree, hard, 1);
    tree = insert_Tree(tree, processor, 1);
    tree = insert_Tree(tree, platter, 3);
    tree = insert_Tree(tree, head, 3);
    tree = insert_Tree(tree, actuator, 3);
    tree = insert_Tree(tree, headArm, 6);
    tree = insert_Tree(tree, slider, 6);
    tree = insert_Tree(tree, rwElement, 6);
    tree = insert_Tree(tree, leadWires, 6);

    run(tree);
}