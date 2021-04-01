#include "textFile.h"

void output_text(char *fileName)
{
    system("CLS");
    
    FILE *file;
    
    char *string = (char*)malloc( (10 * SIZE_OF_STRING) * sizeof(char) );

    file = fopen(fileName, "r");

    fgets(string, 10 * SIZE_OF_STRING, file);
    printf("Your string: %s\n", string);

    fclose(file);
    alarm();

    return;
}