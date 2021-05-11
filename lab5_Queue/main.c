#include "functions.h"
#include "queue.h"

int main()
{
    struct queue *head = NULL;
    struct queue *tail = NULL;

    while (1)
    {
        switch(menu())
        {
            case 1:
                push(&head, &tail);
                break;
            case 2:
                output(head);
                break;
            case 3:
                deleteNode(&head, &tail);
                break;
            case 4:
                search(head);
                break;
            case 5:
                saveInFile(head);
                break;
            case 6:
                loadFromFile(&head, &tail);
                break;
            case 7:
                return 0;
        }
    }
}