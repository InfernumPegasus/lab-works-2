//#include "queue.h"
//#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

    // pointer to the next queue item
    struct animals *next;
};

void getFileName(char* string, int len)     // the function gets file name
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

int inputCheck()
{
    int readCount, isEmpty;
    int number;

    while(1)
    {
        readCount = scanf("%d", &number);
        isEmpty = clearStdin();
        if (readCount == 1 && isEmpty != 0 && number >= 0)
        {
            break;
        }
        printf("Wrong input! Try again: ");
    }

    rewind(stdin);
    return number;
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

    option = inputCheck();
    while(option < 1 || option > 7)
    {
        printf("Wrong input! Try again: ");
        option = inputCheck();
    }

    return option;
}

void putString(char* string, int length)
{
    printf("%s", string);
    for(unsigned long i = strlen(string); i < length; i++)
    {
        printf("%c", ' ');
    }
}

void putHead()
{
    puts("\n");
    puts("-------------------------------------------------");
    puts("| AMOUNT |       NAME       |    DATE    | LIFE |");
    puts("-------------------------------------------------");
}

void push(struct animals **head, struct animals **tail)    // add node to queue
{
    do {
        // allocating memory for a list item
        struct animals *temp = malloc(sizeof(struct animals));

        // temporal int and char variables
        int intTemp;
        char *charTemp;

        // switcher between arrivalDate and lifeDuration
        int typesSwitch;

        printf("Fulfill stack:\n"
               "Enter amount of animals:"
        );
        intTemp = inputCheck();
        while(intTemp < 1)
        {
            printf("Wrong input! Try again: ");
            intTemp = inputCheck();
        }

        temp->animalAmount = intTemp;

        printf("Enter name: ");
        charTemp = getName();
        temp->animalName = charTemp;

        printf("Choose what to input:"
               "\n1 - Arrival date"
               "\n2 - Life duration"
               "\n> ");
        typesSwitch = inputCheck();
        while(typesSwitch < 1 || typesSwitch > 2)
        {
            printf("Wrong input! Try again: ");
            typesSwitch = inputCheck();
        }

        if(typesSwitch == 1)
        {
            temp->typeIndicator = 1;

            do {
                printf("Enter Arrival date: ");
            } while (!getDate(temp->type.arrivalDate));

        } else
        {
            temp->typeIndicator = 2;
            printf("Enter Life duration in months: ");
            intTemp = inputCheck();
            while(intTemp < 1)
            {
                printf("Wrong input! Try again: ");
                intTemp = inputCheck();
            }
            temp->type.lifeDuration = intTemp;
        }

        if (!(*head))
        {
            (*head) = (*tail) = temp;
        } else
        {
            (*tail)->next = temp;
            (*tail) = temp;
            (*tail)->next = NULL;
        }

        printf("Continue?\ny - yes, n - no\n>");
    } while (getchar() == 'y');
}

void printNode(struct animals *temp)    // output single node
{
    printf("|  %3d   | ", temp->animalAmount);
    putString(temp->animalName, 17);
    printf("| ");

    if(temp->typeIndicator == 1)
    {
        printf(" ");
        for (int i = 0; i < 8; i++)
            putchar((char)temp->type.arrivalDate[i]);
        puts("  | ---- |");
    }
    else
    {
        printf("   -----   |");
        printf(" %2d   |", temp->type.lifeDuration);
        printf("\n");
    }
    puts("-------------------------------------------------");
}

void output(struct animals *head)     // output queue
{
    if (!head)
    {
        printf("No info!\n");
        return;
    }

    struct animals *temp = head;

    putHead();
    while (temp)
    {
        printNode(temp);

        temp = temp->next;
    }
}

void deleteNode(struct animals **head,struct animals **tail)
{
    if (!(*head))
    {
        printf("No info!\n");
        return;
    }

    struct animals *pointer = *head;
    struct animals *temp;

    // counting number of nodes in queue
    int nodesAmount = 0;
    temp = (*head);
    while (temp)
    {
        temp = temp->next;
        nodesAmount++;
    }

    int index;

    printf("There are %d nodes in queue now. You can delete nodes from %d to %d\n", nodesAmount, 0,  nodesAmount - 1);
    puts("Enter node number to delete:");

    index = inputCheck();

    while(index < 0 || index > nodesAmount)
    {
        printf("Wrong input! Try again:");
        index = inputCheck();
    }

    // moving through the queue until 'number' node reached
    for (int i = 0; i < index && pointer != NULL; i++)
    {
        pointer = pointer->next;
    }

    if(pointer)
    {
        // case if the end of the queue is reached
        if(pointer == *head)
        {
            // overwriting nodes
            (*head) = (*head)->next;

            puts("\nDeleted successfully!");

            pointer = NULL;
            free(pointer);

            return;
        }

        // case if the pointer is on the last element of the queue
        if (pointer == *tail)
        {
            // overwriting nodes to 'pointer'
            temp = (*head);
            while (temp -> next != pointer)
                temp = temp -> next;

            // overwriting the tail node to the previous one
            *tail = temp;
            (*tail)->next = pointer->next;

            puts("\nDeleted successfully!");

            pointer = NULL;
            temp = NULL;

            free(temp);
            free(pointer);

            return;
        }

        // deleting the node between 'head' and 'tail'
        if(pointer != *head && pointer != *tail)
        {
            temp = (*head);
            while(temp->next != pointer)
                temp = temp->next;
            temp->next = pointer->next;

            puts("\nDeleted successfully!");

            pointer = NULL;
            temp = NULL;

            free(temp);
            free(pointer);

            return;
        }
    }
}

void search(struct animals *head)   // searching in stack by parameter
{
    // temporal pointer to search info in queue
    struct animals *temp;

    if (head == NULL)
    {
        printf("Stack is empty!\n");
        return;
    }

    // temporal variables for searching
    int intTemp;
    char *charTemp;

    // 8 characters in static array is good format for date
    char date[8];
    // variable for search criteria
    int option;
    // number of found nodes in stack
    int found;

    printf("Choose what to search:"
           "\n1 - Amount of animals"
           "\n2 - Animal name"
           "\n3 - Arrival date"
           "\n4 - Life duration"
           "\n5 - Exit"
           "\n>");
    option = inputCheck();
    while(option < 1 || option > 5)
    {
        printf("Wrong input! Try again: ");
        option = inputCheck();
    }

    switch(option)
    {
        case 1:
            temp = head;

            printf("Enter amount for search:");
            intTemp = inputCheck();
            while(intTemp < 1 || intTemp > 999)
            {
                printf("Wrong input! Try again: ");
                intTemp = inputCheck();
            }

            found = 0;

            putHead();
            while(temp)
            {
                if (temp->animalAmount == intTemp)
                {
                    printNode(temp);
                    found++;
                }
                temp = temp->next;
            }
            if(found == 0)
            {
                puts("|                 Nothing found                 |");
                puts("-------------------------------------------------");
            }
            break;

        case 2:
        {
            temp = head;

            printf("Enter name for search:");
            charTemp = getName();

            found = 0;

            putHead();
            while(temp)
            {
                if(strcmp(charTemp, (temp->animalName)) == 0)
                {
                    printNode(temp);
                    found++;
                }
                temp = temp->next;
            }
            if(found == 0)
            {
                puts("|                 Nothing found                 |");
                puts("-------------------------------------------------");
            }
            break;
        }
        case 3:
        {
            temp = head;

            do {
                printf("Enter Arrival date: ");
            } while (!getDate(date));

            found = 0;

            putHead();
            while(temp)
            {
                if(temp->typeIndicator == 1 && strcmp(date, (temp->type.arrivalDate)) == 0)
                {
                    printNode(temp);
                    found++;
                }
                temp = temp->next;
            }
            if(found == 0)
            {
                puts("|                 Nothing found                 |");
                puts("-------------------------------------------------");
            }
            break;
        }
        case 4:
        {
            temp = head;

            printf("Enter life duration:");
            intTemp = inputCheck();
            while(intTemp < 1)
            {
                printf("Wrong input! Try again: ");
                intTemp = inputCheck();
            }

            found = 0;

            putHead();
            while(temp)
            {
                if(temp->typeIndicator == 2 && temp->type.lifeDuration == intTemp)
                {
                    printNode(temp);
                    found++;
                }
                temp = temp->next;
            }
            if(found == 0)
            {
                puts("|                 Nothing found                 |");
                puts("-------------------------------------------------");
            }
            break;
        }
        case 5:
            return;
    }
}

void saveInFile(struct animals *head)   // saving into files
{
    if (head == NULL)
    {
        printf("No info!\n");
        return;
    }

    // file pointer
    FILE *file;

    // filename with fixed 'FILENAME_SIZE' size
    char fileName[FILENAME_SIZE];

    printf("Choose File to save List in"
           "\n1 - Text file"
           "\n2 - Binary file"
           "\n>");
    int fileType;
    fileType = inputCheck();
    while(fileType < 1)
    {
        printf("Wrong input! Try again: ");
        fileType = inputCheck();
    }
    rewind(stdin);

    int i;
    char c = ' ';
    struct animals *temp;

    switch (fileType)
    {
        case 1:
            // saving into .txt file
            temp = head;

            printf("Enter name of .txt File.\n");

            getFileName(fileName, FILENAME_SIZE - 5);
            while(fileNameCheck(fileName) == 1)
            {
                rewind(stdin);
                printf("Wrong name! Try again: ");
                getFileName(fileName, FILENAME_SIZE - 5);
            }

            strcat(fileName, ".txt");   // naming

            // .txt file creation with check
            if(!(file = fopen(fileName, "w")))
            {
                printf("Error!\n");
                return;
            }

            while (temp)
            {
                fprintf(file, "%d ", temp->animalAmount);
                fprintf(file, "%d ", temp->typeIndicator);

                // depending on typeIndicator fulfill arrivalDate or lifeDuration
                if(temp->typeIndicator == 1)
                {
                    for(i = 0; i < 8; i++)
                        fprintf(file, "%c", temp->type.arrivalDate[i]);
                    fprintf(file, "%c", c);
                }
                else
                {
                    fprintf(file, "%d ", temp->type.lifeDuration);
                }

                int len = 0;
                while(temp->animalName[len])
                    len++;
                len++;

                fprintf(file, "%d ", len);

                for(i = 0; i < len; i++)
                {
                    fprintf(file, "%c", temp->animalName[i]);
                }

                temp = temp->next;
            }


            fclose(file);

            break;
        case 2:
            // saving into .bin file
            temp = head;

            printf("Enter name of .bin File.\n");

            getFileName(fileName, FILENAME_SIZE - 5);
            while(fileNameCheck(fileName) == 1)
            {
                rewind(stdin);
                printf("Wrong name! Try again: ");
                getFileName(fileName, FILENAME_SIZE - 5);
            }

            strcat(fileName, ".bin");   // naming

            // .bin file creation with check
            if(!(file = fopen(fileName, "wb")))
            {
                printf("Error!\n");
                return;
            }

            while (temp)
            {
                fwrite(&(temp->animalAmount), sizeof(int), 1, file);
                fwrite(&c, sizeof(char), 1, file);

                fwrite(&(temp->typeIndicator), sizeof(int), 1, file);
                fwrite(&c, sizeof(char), 1, file);

                i = 0;
                if(temp->typeIndicator == 1)
                {
                    while(i < 8)
                    {
                        fwrite(&(temp->type.arrivalDate[i]), sizeof(char), 1, file);
                        i++;
                    }
                    fwrite(&c, sizeof(char), 1, file);
                } else {
                    fwrite(&(temp->type.lifeDuration), sizeof(int), 1, file);
                    fwrite(&c, sizeof(char), 1, file);
                }

                int len = 0;
                while(temp->animalName[len])
                    len++;
                len++;    // strlen with '\0'

                // length of name
                fwrite(&len, sizeof(int), 1, file);
                fwrite(&c, sizeof(char), 1, file);

                for(i = 0; i < len; i++)
                {
                    fwrite(&(temp->animalName[i]), sizeof(char), 1, file);
                }

                temp = temp->next;
            }
            fclose(file);

            break;
    }
    puts("Saved!");
}

void loadFromFile(struct animals **head, struct animals **tail)
{
    int intTemp;
    char c;

    FILE *file;

    int fileType;

    char fileName[FILENAME_SIZE];

    // temporal structural variable
    struct animals *temp = NULL;

    printf("Choose File type to load from"
           "\n1 - Text file"
           "\n2 - Binary file"
           "\n>");
    fileType = inputCheck();
    while(fileType < 1 || fileType > 2)
    {
        printf("Wrong input! Try again: ");
        fileType = inputCheck();
    }
    rewind(stdin);

    switch(fileType)
    {
        case 1:
            printf("Enter name of .txt File.\n");

            getFileName(fileName, FILENAME_SIZE - 5);
            while(fileNameCheck(fileName) == 1)
            {
                rewind(stdin);
                printf("Wrong name! Try again: ");
                getFileName(fileName, FILENAME_SIZE - 5);
            }

            strcat(fileName, ".txt");   // naming

            // opening .txt file with check
            if(!(file = fopen(fileName, "r")))
            {
                printf("File does not exist!\n");
                return;
            }

            while(1)
            {
                if (!(temp = (struct animals *)malloc(1 * sizeof(struct animals))))
                {
                    printf("Out of memory!\n");
                    return;
                }

                fscanf(file, "%d", &intTemp);
                if (feof(file))
                {
                    break;
                }
                temp->animalAmount = intTemp;

                fscanf(file, "%c", &c);

                fscanf(file, "%d", &intTemp);
                temp->typeIndicator = intTemp;

                fscanf(file, "%c", &c);
                if(intTemp == 1)
                {
                    for(int i = 0; i < 8; i++)
                    {
                        fscanf(file, "%c", &c);
                        temp->type.arrivalDate[i] = c;
                    }
                    fscanf(file, "%c", &c);
                } else {
                    fscanf(file, "%d", &intTemp);
                    temp->type.lifeDuration = intTemp;
                    fscanf(file, "%c", &c);
                }

                fscanf(file, "%d", &intTemp);
                fscanf(file, "%c", &c);

                temp->animalName = (char *)malloc(intTemp * sizeof(char));
                for(int i = 0; i < intTemp; i++)
                {
                    fscanf(file, "%c", &c);
                    temp->animalName[i] = c;
                }
                if(!(*head))
                {
                    (*head) = (*tail) = temp;
                } else
                {
                    (*tail) -> next = temp;
                    (*tail) = temp;
                    (*tail) -> next = NULL;
                }
            }

            fclose(file);

            break;

        case 2:

            printf("Enter name of .bin File.\n");

            getFileName(fileName, FILENAME_SIZE - 5);
            while(fileNameCheck(fileName) == 1)
            {
                rewind(stdin);
                printf("Wrong name! Try again: ");
                getFileName(fileName, FILENAME_SIZE - 5);
            }

            strcat(fileName, ".bin");   // naming

            if(!(file = fopen(fileName, "rb")))
            {
                printf("File does not exist!\n");
                return;
            }
            // открытие бинарного файла

            while (1)
            {
                if (!(temp = (struct animals *)malloc(1 * sizeof(struct animals))))
                {
                    printf("Out of memory!\n");
                    return;
                }

                fread(&intTemp, sizeof(int), 1, file);
                if (feof(file))
                {
                    break;
                }

                temp->animalAmount = intTemp;
                fread(&c, sizeof(char), 1, file);

                fread(&intTemp, sizeof(int), 1, file);
                temp->typeIndicator = intTemp;
                fread(&c, sizeof(char), 1, file);
                if(intTemp == 1)
                {
                    for(int i = 0; i < 8; i++)
                    {
                        fread(&c, sizeof(char), 1, file);
                        temp->type.arrivalDate[i] = c;
                    }
                    fread(&c, sizeof(char), 1, file);
                } else {
                    fread(&intTemp, sizeof(int), 1, file);
                    temp->type.lifeDuration = intTemp;
                    fread(&c, sizeof(char), 1, file);
                }

                fread(&intTemp, sizeof(int), 1, file);
                fread(&c, sizeof(char), 1, file);

                temp->animalName = (char *)malloc(intTemp * sizeof(char));
                for(int i = 0; i < intTemp; i++)
                {
                    fread(&c, sizeof(char), 1, file);
                    temp->animalName[i] = c;
                }
                if(!(*head))
                {
                    (*head) = (*tail) = temp;
                } else
                {
                    (*tail) -> next = temp;
                    (*tail) = temp;
                    (*tail) -> next = NULL;
                }
            }

            fclose(file);

            break;
    }
}

int main()
{
    struct animals *head = NULL;
    struct animals *tail = NULL;

    while (1)
    {
        switch(menu())
        {
            case 1:
                push(&head, &tail);
                break;
            case 2:
                output(head);
                break;
            case 3:
                deleteNode(&head, &tail);
                break;
            case 4:
                search(head);
                break;
            case 5:
                saveInFile(head);
                break;
            case 6:
                loadFromFile(&head, &tail);
                break;
            case 7:
                return 0;
        }
    }
}