//
// Created by USER on 16.04.2021.
//

#include "stack.h"
#include "functions.h"

int nodesAmount (struct animals *head)      // amount of nodes in stack
{
    int counter = 0;

    while(head)
    {
        counter++;
        head = head->next;
    }
    return counter;
}

void push(struct animals **head)    // add node to stack
{
    do {
        // allocating memory for a list item
        struct animals *temp = malloc(sizeof(struct animals));

        int intTemp;
        char *charTemp;

        // switch between arrivalDate and lifeDuration
        int typesSwitch;

        if (temp == NULL)
        {
            printf("Stack underflow occurred!\n");
            exit(STACK_UNDERFLOW);
        }
        // storing the pointer to the top of the stack
        temp -> next = *head;

        printf("Fulfill stack:\n"
               "Enter amount of animals:"
        );
        intTemp = input_check();
        while(intTemp < 1)
        {
            printf("Wrong input! Try again: ");
            intTemp = input_check();
        }

        rewind(stdin);
        temp->animalAmount = intTemp;

        printf("Enter name: ");
        charTemp = getName();
        temp->animalName = charTemp;

        printf("Choose what to input:"
               "\n1 - Arrival date"
               "\n2 - Life duration"
               "\n> ");
        typesSwitch = input_check();
        while(typesSwitch < 1 || typesSwitch > 2)
        {
            printf("Wrong input! Try again: ");
            typesSwitch = input_check();
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
            intTemp = input_check();
            while(intTemp < 1)
            {
                printf("Wrong input! Try again: ");
                intTemp = input_check();
            }
            temp->type.lifeDuration = intTemp;
        }

        // assign a pointer to the top of the stack to the pointer of the created element
        *head = temp;
        printf("Continue?\ny - yes, n - no\n>");
    } while (getchar() == 'y');
}

void printNode(struct animals *head)     // output node
{
    struct animals *ptr = head;

    if (ptr == NULL)
    {
        printf("Node cannot be achieved!\n");
        return;
    }

    printf("Node >\n");
    printf("Amount of animals: %d\n", ptr->animalAmount);
    printf("Animal name: %s\n",ptr->animalName);

    if(ptr->typeIndicator == 1)
    {
        printf("Arrival date: ");
        for(int i = 0; i < 8; i++)
            putchar((char)ptr->type.arrivalDate[i]);
    }
    else
    {
        printf("Life duration: %d\n", ptr->type.lifeDuration);
    }
    printf("\n\n");
}

void printStack(struct animals *head)     // output stack
{
    struct animals *ptr = head;

    if (ptr == NULL)
    {
        printf("Node cannot be achieved!\n");
        return;
    }

    printf("Your list:\n");
    while (ptr)
    {
        printf("Node >\n");
        printf("Amount of animals: %d\n", ptr->animalAmount);
        printf("Animal name: %s\n",ptr->animalName);

        if(ptr->typeIndicator == 1)
        {
            printf("Arrival date: ");
            for(int i = 0; i < 8; i++)
                putchar((char)ptr->type.arrivalDate[i]);
        }
        else
        {
            printf("Life duration: %d\n", ptr->type.lifeDuration);
        }
        printf("\n\n");
        ptr = ptr->next;
    }
}

void search(struct animals *head)   // searching in stack by parameter
{
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
    // index for node output
    int index;
    // number of found nodes in stack
    int found;

    printf("Choose what to search:"
           "\n1 - Amount of animals"
           "\n2 - Animal name"
           "\n3 - Arrival date"
           "\n4 - Life duration"
           "\n5 - Exit"
           "\n>");
    option = input_check();
    while(option < 1 || option > 5)
    {
        printf("Wrong input! Try again: ");
        option = input_check();
    }

    switch(option)
    {
        case 1:
            rewind(stdin);
            temp = head;

            printf("Enter amount for search:");
            intTemp = input_check();
            while(intTemp < 1)
            {
                printf("Wrong input! Try again: ");
                intTemp = input_check();
            }

            index = 0;
            found = 0;

            while(temp || index++ < nodesAmount(temp))
            {
                if (temp->animalAmount == intTemp)
                {
                    printNode(temp);
                    found++;
                }
                temp = temp->next;
            }
            if(found == 0)
                printf("Nothing found!\n");
            printf("\n\n");
            break;

        case 2:
        {
            rewind(stdin);
            temp = head;

            printf("Enter name for search:");
            charTemp = getName();

            index = 0;
            found = 0;

            while(temp || index++ < nodesAmount(temp))
            {
                if(strcmp(charTemp, (temp->animalName)) == 0)
                {
                    printNode(temp);
                    found++;
                }
                temp = temp->next;
            }
            if(found == 0)
                printf("Nothing found!\n");

            printf("\n\n");
            break;
        }
        case 3:
        {
            rewind(stdin);
            temp = head;

            do {
                printf("Enter Arrival date: ");
            } while (!getDate(date));

            index = 0;
            found = 0;

            while(temp || index++ < nodesAmount(temp))
            {
                if(temp->typeIndicator == 1 && strcmp(date, (temp->type.arrivalDate)) == 0)
                {
                    printNode(temp);
                    found++;
                }
                temp = temp->next;
            }
            if(found == 0)
                printf("Nothing found!\n");
            printf("\n\n");
            break;
        }
        case 4:
        {
            rewind(stdin);
            temp = head;

            printf("Enter life duration:");
            intTemp = input_check();
            while(intTemp < 1)
            {
                printf("Wrong input! Try again: ");
                intTemp = input_check();
            }

            index = 0;
            found = 0;

            while(temp || index++ < nodesAmount(temp))
            {
                if(temp->typeIndicator == 2 && temp->type.lifeDuration == intTemp)
                {
                    printNode(temp);
                    found++;
                }
                temp = temp->next;
            }
            if(found == 0)
                printf("Nothing found!\n");
            printf("\n\n");
            break;
        }
        case 5:
            return;
    }
}

struct animals *nodeDelete (struct animals *head, int number)    // deleting node with number from stack
{
    // auxiliary pointer
    struct animals *ptr;
    // saving the current root of the list
    struct animals *current = head;

    // go to the 'number' element
    for(int i = 1; i < number && current != NULL; i++)
    {
        current = current->next;
    }
    if(current != NULL)
    {
        if (current == head)
        {
            head = head->next;
            free(current);
            // если текущий узел = корню списка, то очищаем текущий узел
        } else {
            ptr = head;
            // используем временный указатель ptr для сохранения корня списка
            while (ptr->next != current)
                ptr = ptr->next;
            // продвигаемся по списку, пока не достигнем текущего указателя current
            ptr->next = current->next;
            // производим перезапись соответствующих элементов ptr и current
            free(current);
            // очищаем ненужный указатель current
        }
    }
    return head;
}

void saveInFile(struct animals *head)   // saving into files
{
    if (head == NULL)
    {
        printf("Node cannot be achieved!\n");
        return;
    }

    // указатель на файл
    FILE *file;

    // имя файла
    char fileName[FILENAME_SIZE];

    printf("Choose File to save List in"
           "\n1 - Text file"
           "\n2 - Binary file"
           "\n>");
    int fileType;
    fileType = input_check();
    while(fileType < 1)
    {
        printf("Wrong input! Try again: ");
        fileType = input_check();
    }
    rewind(stdin);

    int i;
    char c = ' ';
    struct animals *temp = head;

    switch (fileType)
    {
        case 1:
            // сохранение в текстовый файл  // TODO
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

            if(!(file = fopen(fileName, "w")))
            {
                printf("Error!\n");
                return;
            }
            // создание текстового файла

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
            // сохранение в бинарный файл
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

            if(!(file = fopen(fileName, "wb")))
            {
                printf("Error!\n");
                return;
            }
            // создание бинарного файла

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

                fwrite(&len, sizeof(int), 1, file);     // length of name
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
}

void loadFromFile(struct animals **head)
{
    int intTemp;
    char c;

    FILE *file;

    int fileType;

    char fileName[FILENAME_SIZE];

    // temporal structural variable
    struct animals *temp = NULL, *pointer = NULL, *varStack = NULL;

    printf("Choose File type to load from"
           "\n1 - Text file"
           "\n2 - Binary file"
           "\n>");
    fileType = input_check();
    while(fileType < 1 || fileType > 2)
    {
        printf("Wrong input! Try again: ");
        fileType = input_check();
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

            if(!(file = fopen(fileName, "r")))
            {
                printf("File does not exist!\n");
                return;
            }
            // opening .txt file

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

                temp->next = pointer;

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
                pointer = temp;
            }

            temp = NULL;
            while (pointer)
            {
                varStack = pointer->next;
                pointer->next = temp;
                temp = pointer;
                pointer = varStack;
            }
            (*head) = temp;

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

                temp->next = pointer;

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

                pointer = temp;
            }

            temp = NULL;
            while (pointer)
            {
                varStack = pointer->next;
                pointer->next = temp;
                temp = pointer;
                pointer = varStack;
            }
            (*head) = temp;

            fclose(file);

            break;
    }
}
