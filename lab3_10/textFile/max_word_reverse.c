#include "textFile.h"

void max_word_reverse(char *fileName)
{
    system("CLS");
    
    FILE *file;
    
    int length = 0;
    char symbol;
    fpos_t leftBorder, rightBorder, maxWordPos;
    
    file = fopen(fileName, "r+");
    
    while(1)
    {
        while (!(feof(file)))
        {
            fgetpos(file, &leftBorder);
            fscanf(file, "%c", &symbol);
            if (symbol != ' ')
                break;
        }
        
        if (feof(file))
            break;

        while (!feof(file) && symbol != ' ' && symbol != '\n')
        {
            fgetpos(file, &rightBorder);
            fscanf(file, "%c", &symbol);
        }
        
        if (rightBorder - leftBorder > length)
        {
            length = rightBorder - leftBorder;
            maxWordPos = leftBorder;
        }
    }
    
    rewind(file);
    
    fsetpos(file, &maxWordPos);

    printf("\nMax word len: %d\n", length);
    printf("Max pos: %lld\n", maxWordPos);
    
    printf("\n");
    system("pause");
    
    fclose(file);
    
    reverse(fileName, maxWordPos, maxWordPos + length - 1);
    
    output_text(fileName);
    
    fclose(file);
    return;
}