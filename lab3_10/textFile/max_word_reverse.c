#include "textFile.h"

void max_word_reverse(FILE *file, char *fileName)
{
    system("CLS");
    
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
    printf("Max pos: %llu\n", maxWordPos);
    
    fsetpos(file, &maxWordPos);
    // установка позиции на начало макс слова
    
    char left_c, right_c, temp_c;
    // буферные переменные символов
    
    fpos_t left_i, right_i;
    // буферные переменные позиций
    
    
    for (left_i = maxWordPos, right_i = maxWordPos + length - 1; left_i < right_i; left_i++, right_i--)
    {
        fsetpos(file, &left_i);
        fscanf(file, "c", &left_c);
        
        fsetpos(file, &right_i);
        fscanf(file, "c", &right_c);
        
        temp_c = left_c;
        left_c = right_c;
        right_c = temp_c;
        
        fsetpos(file, &left_i);
        printf("%c", right_c);
        
        fsetpos(file, &right_i);
        printf("%c", left_c);
    }
    
    fclose(file);
    
    reverse(fileName, maxWordPos, maxWordPos + length - 1);
    
    output_text(file, fileName);
    
    fclose(file);
    return;
}