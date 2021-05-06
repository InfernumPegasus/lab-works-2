//
// Created by USER on 16.04.2021.
//

#ifndef LAB4_STACK_STACK_H
#define LAB4_STACK_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// stack underflow error code
#define STACK_UNDERFLOW -101
// maximum length of file name
#define FILENAME_SIZE 20

struct animals
{
    int animalAmount;
    char *animalName;

    union types
    {
        char arrivalDate[8];
        int lifeDuration;
    } type;

    /* indicator: whether ArrivalDate or lifeDuration is selected
    *  1 - field arrivalDate is chosen
    *  2 - field lifeDuration is chosen
    */
    int typeIndicator;

    // pointer to the next list item
    struct animals *next;
};

int nodesAmount (struct animals *head);                     // amount of nodes in stack
void push(struct animals **head);                           // add node to stack
void printNode(struct animals *head);                       // output node
void printStack(struct animals *head);                      // output stack
void search(struct animals *head);                          // searching in stack by parameter
struct animals *nodeDelete (struct animals *head, int );    // deleting node with number from stack
void saveInFile(struct animals *head);                      // saving into files
void loadFromFile(struct animals **head);                   // reading from files

#endif //LAB4_STACK_STACK_H
