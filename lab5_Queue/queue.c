//
// Created by USER on 09.05.2021.
//

#include "functions.h"
#include "queue.h"

struct info getInfo()   // get info from user
{
    // structural variable which contains info
    struct info temp;

    printf("Enter animal amount:");
    temp.animalAmount = inputCheck();
    while( temp.animalAmount < 0 )
    {
        printf("Wrong input! Try again:");
        temp.animalAmount = inputCheck();
    }

    printf("Enter name:");
    temp.animalName = getName();

    printf("Choose what to input:"
           "\n1 - Arrival date"
           "\n2 - Life duration"
           "\n> ");
    temp.typeIndicator = inputCheck();
    while ( temp.typeIndicator < 1 || temp.typeIndicator > 2 )
    {
        printf("Wrong input! Try again:");
        temp.typeIndicator = inputCheck();
    }

    if (temp.typeIndicator == 1)
    {
        do {
            printf("Enter arrival date: ");
        } while ( !(getDate(temp.type.arrivalDate)) );
    } else {
        printf("Enter life duration (in months): ");
        temp.type.lifeDuration = inputCheck();
        while( temp.type.lifeDuration < 1 || temp.type.lifeDuration > 99 )
        {
            printf("Wrong input! Try again:");
            temp.type.lifeDuration = inputCheck();
        }
    }

    return temp;
}

void push(struct queue **head, struct queue **tail)    // add node to queue
{
    do {
        // allocating memory for a queue item
        struct queue *temp = malloc(sizeof(struct queue));
        // getting info
        struct info animalInfo = getInfo();

        // fulfilling node
        temp->singleAnimal.animalAmount = animalInfo.animalAmount;
        temp->singleAnimal.animalName = animalInfo.animalName;
        temp->singleAnimal.typeIndicator = animalInfo.typeIndicator;
        if (animalInfo.typeIndicator == 1)
        {
            for (int i = 0; i < 8; i++)
                temp->singleAnimal.type.arrivalDate[i] = animalInfo.type.arrivalDate[i];
        } else {
            temp->singleAnimal.type.lifeDuration = animalInfo.type.lifeDuration;
        }

        // if there are no nodes in queue
        // create queue from 'temp' pointer
        if (!(*head))
        {
            (*head) = (*tail) = temp;
        } else {
            // else just add node to queue
            // and initialize next element with NULL
            (*tail)->next = temp;
            (*tail) = temp;
            (*tail)->next = NULL;
        }

        printf("Continue?\ny - yes, n - no\n>");
    } while (getchar() == 'y');
}

void printNode(struct queue *temp)    // output single node
{
    printf("|  %3d   | ", temp->singleAnimal.animalAmount);
    putString(temp->singleAnimal.animalName, 17);
    printf("| ");

    if(temp->singleAnimal.typeIndicator == 1)
    {
        printf(" ");
        for (int i = 0; i < 8; i++)
            putchar((char)temp->singleAnimal.type.arrivalDate[i]);
        puts("  | ---- |");
    }
    else
    {
        printf("   -----   |");
        printf(" %2d   |", temp->singleAnimal.type.lifeDuration);
        printf("\n");
    }
    puts("-------------------------------------------------");
}

void output(struct queue *head)     // output queue
{
    if (!head)
    {
        printf("No info!\n");
        return;
    }

    struct queue *temp = head;

    putHead();
    while (temp)
    {
        printNode(temp);

        temp = temp->next;
    }
}

void deleteNode(struct queue **head, struct queue **tail)       // deleting node
{
    if (!(*head))
    {
        printf("No info!\n");
        return;
    }

    struct queue *pointer = *head;
    struct queue *temp;

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

void search(struct queue *head)   // searching in stack by parameter
{
    // temporal pointer to search info in queue
    struct queue *temp;

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

    while (1)
    {
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

        switch (option)
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
                    if (temp->singleAnimal.animalAmount == intTemp)
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
                    if(strcmp(charTemp, (temp->singleAnimal.animalName)) == 0)
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
                    if(temp->singleAnimal.typeIndicator == 1 && strcmp(date, (temp->singleAnimal.type.arrivalDate)) == 0)
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
                    if(temp->singleAnimal.typeIndicator == 2 && temp->singleAnimal.type.lifeDuration == intTemp)
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
}

void saveInFile(struct queue *head)   // saving into files
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
    struct queue *temp;

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
                fprintf(file, "%d ", temp->singleAnimal.animalAmount);
                fprintf(file, "%d ", temp->singleAnimal.typeIndicator);

                // depending on typeIndicator fulfill arrivalDate or lifeDuration
                if(temp->singleAnimal.typeIndicator == 1)
                {
                    for(i = 0; i < 8; i++)
                        fprintf(file, "%c", temp->singleAnimal.type.arrivalDate[i]);
                    fprintf(file, "%c", c);
                }
                else
                {
                    fprintf(file, "%d ", temp->singleAnimal.type.lifeDuration);
                }

                int len = 0;
                while(temp->singleAnimal.animalName[len])
                    len++;
                len++;

                fprintf(file, "%d ", len);

                for(i = 0; i < len; i++)
                {
                    fprintf(file, "%c", temp->singleAnimal.animalName[i]);
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
                fwrite(&(temp->singleAnimal.animalAmount), sizeof(int), 1, file);
                fwrite(&c, sizeof(char), 1, file);

                fwrite(&(temp->singleAnimal.typeIndicator), sizeof(int), 1, file);
                fwrite(&c, sizeof(char), 1, file);

                i = 0;
                if(temp->singleAnimal.typeIndicator == 1)
                {
                    while(i < 8)
                    {
                        fwrite(&(temp->singleAnimal.type.arrivalDate[i]), sizeof(char), 1, file);
                        i++;
                    }
                    fwrite(&c, sizeof(char), 1, file);
                } else {
                    fwrite(&(temp->singleAnimal.type.lifeDuration), sizeof(int), 1, file);
                    fwrite(&c, sizeof(char), 1, file);
                }

                int len = 0;
                while(temp->singleAnimal.animalName[len])
                    len++;
                len++;    // strlen with '\0'

                // length of name
                fwrite(&len, sizeof(int), 1, file);
                fwrite(&c, sizeof(char), 1, file);

                for(i = 0; i < len; i++)
                {
                    fwrite(&(temp->singleAnimal.animalName[i]), sizeof(char), 1, file);
                }

                temp = temp->next;
            }
            fclose(file);

            break;
    }
    puts("Saved!");
}

void loadFromFile(struct queue **head, struct queue **tail)     // loading info from files
{
    int intTemp;
    char c;

    FILE *file;

    int fileType;

    char fileName[FILENAME_SIZE];

    // temporal structural variable
    struct queue *temp = NULL;

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
                if (!(temp = (struct queue *)malloc(1 * sizeof(struct queue))))
                {
                    printf("Out of memory!\n");
                    return;
                }

                fscanf(file, "%d", &intTemp);
                if (feof(file))
                {
                    break;
                }
                temp->singleAnimal.animalAmount = intTemp;

                fscanf(file, "%c", &c);

                fscanf(file, "%d", &intTemp);
                temp->singleAnimal.typeIndicator = intTemp;

                fscanf(file, "%c", &c);
                if(intTemp == 1)
                {
                    for(int i = 0; i < 8; i++)
                    {
                        fscanf(file, "%c", &c);
                        temp->singleAnimal.type.arrivalDate[i] = c;
                    }
                    fscanf(file, "%c", &c);
                } else {
                    fscanf(file, "%d", &intTemp);
                    temp->singleAnimal.type.lifeDuration = intTemp;
                    fscanf(file, "%c", &c);
                }

                fscanf(file, "%d", &intTemp);
                fscanf(file, "%c", &c);

                temp->singleAnimal.animalName = (char *)malloc(intTemp * sizeof(char));
                for(int i = 0; i < intTemp; i++)
                {
                    fscanf(file, "%c", &c);
                    temp->singleAnimal.animalName[i] = c;
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
                if (!(temp = (struct queue *)malloc(1 * sizeof(struct queue))))
                {
                    printf("Out of memory!\n");
                    return;
                }

                fread(&intTemp, sizeof(int), 1, file);
                if (feof(file))
                {
                    break;
                }

                temp->singleAnimal.animalAmount = intTemp;
                fread(&c, sizeof(char), 1, file);

                fread(&intTemp, sizeof(int), 1, file);
                temp->singleAnimal.typeIndicator = intTemp;
                fread(&c, sizeof(char), 1, file);
                if(intTemp == 1)
                {
                    for(int i = 0; i < 8; i++)
                    {
                        fread(&c, sizeof(char), 1, file);
                        temp->singleAnimal.type.arrivalDate[i] = c;
                    }
                    fread(&c, sizeof(char), 1, file);
                } else {
                    fread(&intTemp, sizeof(int), 1, file);
                    temp->singleAnimal.type.lifeDuration = intTemp;
                    fread(&c, sizeof(char), 1, file);
                }

                fread(&intTemp, sizeof(int), 1, file);
                fread(&c, sizeof(char), 1, file);

                temp->singleAnimal.animalName = (char *)malloc(intTemp * sizeof(char));
                for(int i = 0; i < intTemp; i++)
                {
                    fread(&c, sizeof(char), 1, file);
                    temp->singleAnimal.animalName[i] = c;
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
