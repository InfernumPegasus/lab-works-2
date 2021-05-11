//
// Created by USER on 09.05.2021.
//

#ifndef LAB5_QUEUE_QUEUE_H
#define LAB5_QUEUE_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// maximum length of file name
#define FILENAME_SIZE 20

struct info
{
    int animalAmount;
    char *animalName;

    /* indicator: whether ArrivalDate or lifeDuration is selected
    *  1 - field arrivalDate is chosen
    *  2 - field lifeDuration is chosen
    */
    int typeIndicator;

    union types
    {
        char arrivalDate[8];
        int lifeDuration;
    } type;
};

struct queue
{
    // structural variable that contains info about single animal
    struct info singleAnimal;
    // structural pointer to next node in queue
    struct queue *next;
};

struct info getInfo();      // getting info from user
void push(struct queue **head, struct queue **tail);

void printNode(struct queue *temp);    // output single node
void output(struct queue *head);     // output queue

void deleteNode(struct queue **head, struct queue **tail);      // deleting node

void search(struct queue *head);   // searching in stack by parameter

void saveInFile(struct queue *head);   // saving into files
void loadFromFile(struct queue **head, struct queue **tail);    // loading info from files

#endif //LAB5_QUEUE_QUEUE_H
