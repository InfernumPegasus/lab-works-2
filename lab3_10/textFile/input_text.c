#include "textFile.h"

void input_text(char *fileName)
{
    system("CLS");
    
    FILE *file;
    
    char *string = (char*)malloc( (10 * SIZE_OF_STRING) * sizeof(char) );

    file = fopen(fileName, "w");

    printf("Fulfill file with words.\n");
    getstr(string, 10 * SIZE_OF_STRING);

    fprintf(file, "%s", string);

    fclose(file);
    //free(string);
    alarm();
    return;
}