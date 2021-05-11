//
// Created by USER on 09.05.2021.
//

#ifndef LAB5_QUEUE_FUNCTIONS_H
#define LAB5_QUEUE_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void getFileName(char* string, int len);     // the function gets file name
int fileNameCheck(const char *string);     // the function checks the correctness of the entered file name
char* getName(void);     // function to get animalName
bool getDate(char str[8]);   // boolean function for inputting and checking date format

int clearStdin();
int inputCheck();

int menu();  // UI-menu

void putString(char* string, int length);
void putHead();

#endif //LAB5_QUEUE_FUNCTIONS_H
