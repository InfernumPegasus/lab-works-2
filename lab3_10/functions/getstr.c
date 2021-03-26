#include "functions.h"

void getstr(char* string, int len)
{
    char buf; // buffer for each character

    while((buf = getchar()) != '\n' && --len > 0)
        *string++ = buf;

    *string = '\0';

    return;
}