#ifndef TEXTFILE_H
#define TEXTFILE_H

#define SIZE_OF_STRING 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input_text(char*);

void output_text(char*);

void word_count(char*);

void max_word_reverse(char*);

void reverse(char*, fpos_t, fpos_t);

#endif // TEXTFILE_H

