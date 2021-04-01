#include "textFile.h"

void word_count(char *fileName)
{
    system("CLS");
    
    FILE *file;
    
    char *string = (char*)malloc( (10 * SIZE_OF_STRING) * sizeof(char) );
    int counter = 0;
    
    file = fopen(fileName, "r+");
    
    printf("Words in the file:\n");
    while (fscanf(file, "%s", string) == 1)
    {
        counter++;
        printf("%s\n", string);
    }
    
    printf("\nNumber of words: %d\n", counter);
    
    fclose(file);
    
    alarm();
    
    return;
}