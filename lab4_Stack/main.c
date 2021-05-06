#include "stack.h"
#include "functions.h"

/*
   Задание:
1. Добавление элементов в стек. (есть)
2. Просмотр стека. (есть)
3. Удаление из стека. Реализовать функцию для удаления любого элемента из стека по номеру.  (есть)
4. Поиск в стеке. Реализовать функцию поиска элементов стека по параметрам(как в ЛР1-2). (есть)
5. Сохранение списка в файлы(текстовый И бинарный).
6. Загрузка списка из файлов(текстового И бинарного).
*/

int main()
{
    struct animals *head = NULL;

    int deletionIndex;

    while (1)
    {
        switch(menu())
        {
            case 1:
                push(&head);

                break;
            case 2:
                printStack(head);

                break;
            case 3:
                printf("Enter number of the node to delete:");
                deletionIndex = input_check();

                while(deletionIndex < 0 || deletionIndex > nodesAmount(head))
                {
                    printf("Wrong input! Try again: ");
                    deletionIndex = input_check();
                }

                if(deletionIndex < nodesAmount(head))
                    head = nodeDelete(head, deletionIndex);
                break;
            case 4:
                search(head);
                break;
            case 5:
                saveInFile(head);
                break;
            case 6:
                loadFromFile(&head);
                break;
            case 7:
                return 0;
        }
    }
}











