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
*   - 2.1 - С клавиатуры заполнить файл целыми числами. (DONE)
*   - 2.2 - Найти и напечатать номер элемента, произведение которого с предыдущим элементом минимально. (DONE)
*   - 2.3 - Попарно поменять элементы местами. Если их количество нечетное, последний элемент оставить на месте.
*
*   РЕМАРКА:
*   - Имя файла задаётся с клавиатуры, предусмотрена защита от некорректных данных внутри файла.
*
**/
/*
int amount_of_numbers(char* fileName)
{
    int amount = 0;
    int num;
    
    FILE *file;
    
    file = fopen(fileName, "rb");
    
    while (fread(&num, sizeof(int), 1, file))
    {
        amount++;
    }
    
    fclose(file);
    
    return amount;
}
*/
void input_bin(char *fileName, int amount)
{
    system("CLS");
    
    FILE *file;
    
    file = fopen(fileName, "wb");
    
    int index;
    
    printf("Enter %d numbers:\n", amount);
    for(index = 0; index < amount; index++)
    {
        int number;
        
        scanf("%d", &number);
        
        fwrite(&number, sizeof(int), 1, file);
    }
    
    fclose(file);
    
    return;
}

void output_bin(char *fileName, int amount)
{
    system("CLS");
    
    FILE *file;
    
    file = fopen(fileName, "rb");
    
    int number;
    
    for (int i = 0; i < amount; i++)
    {
        fread(&number, sizeof(int), 1, file);
        
        printf("%d\n", number);
    }
    
    fclose(file);
    
    alarm();
    
    return;
}

void sum(FILE *file, char *fileName)
{
    system("CLS");
    
    file = fopen(fileName, "rb");
    
    int counter = 0;
    int number;
    
    int sum = 0;
    
    while (!feof(file))
    {
        if (fscanf(file, "%d", &number))
        {
            counter++;
            
            if(counter %2 == 0)
            {
                sum += number;
            }
            
        }
    }
    
    printf("Counter = %d\nSum = %d\n", counter, sum);
    
    alarm();
    
    fclose(file);
    
    return;
}

void min_mult(char *fileName)
{
    system("CLS");
    
    FILE *file;
    
    file = fopen(fileName, "rb");
    
    int tempMult;
    int firstNumber, secondNumber, tempMin;
    
    fread(&firstNumber, sizeof(int), 1, file);
    //fseek(file, SEEK_CUR, sizeof(int));
    fread(&secondNumber, sizeof(int), 1, file);
    tempMult = firstNumber * secondNumber;
    // setting initial values
    
    rewind(file);
    while(!feof(file))
    {
        fread(&firstNumber, sizeof(int), 1, file);
        fread(&secondNumber, sizeof(int), 1, file);
        
        if(firstNumber * secondNumber < tempMult)
        {
            tempMin = secondNumber;
            tempMult = firstNumber * secondNumber;
        }
    }
    
    
    printf("Minimal Multiplication = %d\n", tempMult);
    
    fclose(file);
    
    alarm();
    
    return;
}

void num_reverse(char *fileName, int amount)
{
    system("CLS");
    
    FILE* file;
    
    file = fopen(fileName, "r+b");
    
    //-----------
    
    int firstNumber, secondNumber;
    
    rewind(file);
    for(int i = 1; i < amount && i + 1 < amount; i++)
    {
        fread(&firstNumber, sizeof(int), 1, file);
        fread(&secondNumber, sizeof(int), 1, file);
        
        fseek(file, -2 * sizeof(int), SEEK_CUR);
        fwrite(&secondNumber, sizeof(int), 1, file);
        fwrite(&firstNumber, sizeof(int), 1, file);
    }
    // доделать
    
    fclose(file);
    
    system("pause");
    
    output_bin(fileName, amount);
    
    return;
}





int main()
{
    int fileType;
    int option;
    
    int numberAmount;

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
                input_text(fileName);
                break;
            case 2:
                output_text(fileName);
                break;
            case 3:
                word_count(fileName);
                break;
            case 4:
                max_word_reverse(fileName);
                break;
            case 5:
                return 0;
            }
            
        } while(1);

        break;

    case 2:
        
        printf("\nEnter name of .bin File.\n");

        getstr(fileName, SIZE_OF_STRING - 5);

        strcat(fileName, ".bin");   // naming

        binaryFile = fopen(fileName, "w+b");
        fclose(binaryFile);
        
        printf("\nEnter amount of numbers: ");
        scanf("%d", &numberAmount);
        
        do
        {
            printf("Choose option"
                   "\n1 - Input"
                   "\n2 - Output"
                   "\n3 - Find minimal multiply"
                   "\n4 - Pair swap"
                   "\n5 - Exit"
                   "\n\nYour choice: ");
                   
            scanf("%d", &option);
            
            switch (option)
            {
            case 1:
                input_bin(fileName, numberAmount);
                
                break;
                
            case 2:
                output_bin(fileName, numberAmount);
                
                break;
                
            case 3:
                
                min_mult(fileName);
                
                break;
                
            case 4:
                
                num_reverse(fileName, numberAmount);
                
                break;
                
            case 5:
                
                return 0;
            }
            
        } while (1);
        
        
        
        break;
    }

    return 0;
}







