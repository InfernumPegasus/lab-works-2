//
// Created by USER on 16.04.2021.
//

#include "functions.h"

void getFileName(char* string, int len)     // the function returns the file name
{
    char buf; // buffer for each character

    while((buf = (char)getchar()) != '\n' && --len > 0)
        *string++ = buf;

    *string = '\0';
}

int fileNameCheck(char *string)     // the function checks the correctness of the entered file name
{
    int i = 0;

    while(string[i])
    {
        if(string[i] == '/' || string[i] == '~' || string[i] == '|' || string[i] == '\\' || string[i] == '<' || string[i] == '>' ||
           string[i] == '{' || string[i] == '}' || string[i] == '[' || string[i] == ']' || string[i] == '%' || string[i] == '&' ||
           string[i] == '+' || string[i] == '?' || string[i] == '"' || string[i] == '*' || string[i] == ':' || string[i] == '#' ||
           string[i] == '@' || string[i] == '=' || string[i] == '$')
        {
            return 1;
        }

        i++;
    }
    return 0;
}

int menu()  // UI-menu
{
    int option;

    printf("Choose option:"
           "\n1 - Create/add info to stack"
           "\n2 - Output stack"
           "\n3 - Delete element from stack"
           "\n4 - Find info in stack"
           "\n5 - Save info in file"
           "\n6 - Load from file"
           "\n7 - Exit"
           "\n> ");

    option = input_check();
    while(option < 1 || option > 7)
    {
        printf("Wrong input! Try again: ");
        option = input_check();
    }

    return option;
}

char* getName(void)     // function to get animalName
{
    rewind(stdin);

    char* str = NULL;
    char c;
    size_t i;

    for (i = 0; (c = (char)getchar()) != '\n'; ++i)
    {
        // character check
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
        {
            puts("Invalid input, try again!");
            system("pause>0");
            return NULL;
        }
        // reallocation check
        if (!(str = (char*)realloc(str, i + 2)))
        {
            puts("Not enough memory!");
            system("pause>0");
            return NULL;
        }
        // converts letters to the correct case
        (c >= 'A' && c <= 'Z') ? str[i] = (char)(c + ('a' - 'A')) : (str[i] = c);
    }
    if (str) str[i] = '\0';
    return str;
}

bool getDate(char str[8])   // boolean function for inputting and checking date format
{
    size_t i;
    rewind(stdin);
    for (i = 0; i < 8; i++)
        if (((i == 2 || i == 4) && (char)getchar() != '.') || ((str[i] = (char)getchar()) < '0' || str[i] > '9'))
        {
            puts("Invalid input, try again!");
            system("pause>0");
            return false;
        }
    if ((str[2] == '1' && str[3] > '2') || str[2] > '1' || str[0] > '3' || (str[0] == '3' && str[1] > 1))
    {
        puts("Such date don't exist!");
        system("pause>0");
        rewind(stdin);
        return false;
    }
    rewind(stdin);
    return true;
}

int input_check()
{
    int readCount, isEmpty;
    int number;

    while(1)
    {
        readCount = scanf("%d", &number);
        isEmpty = clearStdin();
        if(readCount == 1 && isEmpty != 0 && number >= 0)
        {
            break;
        }
        printf("Wrong input! Try again: ");
    }

    rewind(stdin);
    return number;
}

int clearStdin()
{
    int rv = 1, ch;
    while (1)
    {
        ch = getchar();
        if (ch == '\n' || ch == EOF)
        {
            break;
        }
        rv = 0;
    }
    return rv;
}