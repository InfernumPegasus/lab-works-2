//
// Created by USER on 16.04.2021.
//

#ifndef LAB4_STACK_FUNCTIONS_H
#define LAB4_STACK_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void getFileName(char* string, int len);          // the function returns the file name
int fileNameCheck(char *string);                  // the function checks the correctness of the entered file name
int menu();                                       // UI-menu
char* getName(void);                              // function to get animalName
bool getDate(char str[8]);                        // boolean function for inputting and checking date format
int input_check();
int clearStdin();

#endif //LAB4_STACK_FUNCTIONS_H
