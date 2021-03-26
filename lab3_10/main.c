#include "textFile/textFile.h"
#include "functions/functions.h"

/**
*   Т.З:
*   - 1 - текстовый файл
*
*   - 1.1 - С клавиатуры заполнить файл словами. Вывести содержимое файла на экран. (DONE)
*   - 1.2 - Посчитать количество слов в файле.  (DONE)
*   - 1.3 - Сделать реверс самого длинного слова в файле. (DONE)
*
*
*   - 2 - бинарный файл
*
*   - 2.1 - С клавиатуры заполнить файл целыми числами.
*   - 2.2 - Найти и напечатать номер элемента, произведение которого с предыдущим элементом минимально.
*   - 2.3 - Попарно поменять элементы местами. Если их количество нечетное, последний элемент оставить на месте.
*
*   РЕМАРКА:
*   - Имя файла задаётся с клавиатуры, предусмотрена защита от некорректных данных внутри файла.
*
**/

int main()
{
    int fileType;
    int option;

    FILE *binaryFile = NULL;
    FILE *textFile = NULL;

    char *fileName = (char*)malloc( (SIZE_OF_STRING - 5) * sizeof(char) );

    printf("Choose file to work with:"
           "\n1 - Text file"
           "\n2 - Binary file"
           "\n\nYour choice: ");
    scanf("%d", &fileType);

    rewind(stdin);

    switch(fileType)
    {
    case 1:
        
        printf("\nEnter name of .txt File.\n");

        getstr(fileName, SIZE_OF_STRING - 5);

        strcat(fileName, ".txt");   // naming

        textFile = fopen(fileName, "r+a");
        fclose(textFile);

        do
        {
            printf("Choose option: ");
            printf("\n1 - Input"
                   "\n2 - Output"
                   "\n3 - Count number of words"
                   "\n4 - Reverse max word"
                   "\n5 - Exit"
                   "\nYour choice: "
                   );
            scanf("%d", &option);
            rewind(stdin);
            
            switch(option)
            {
            case 1:
                input_text(textFile, fileName);
                break;
            case 2:
                output_text(textFile, fileName);
                break;
            case 3:
                word_count(textFile, fileName);
                break;
            case 4:
                max_word_reverse(textFile, fileName);
                break;
            case 5:
                return 0;
            }
            
        } while(1);
        
        
        
        
        

        break;

    case 2:
        break;
    }

    return 0;
}













