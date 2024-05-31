#ifndef TRANSLATOR_H
#define TRANSLATOR_H

//requirements  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//if the last char is a '\n', it is replaced with '\0' to end the line
void remove_new_line(char *str);

//remove the space in string
void remove_space(char *string);

//remove empty lines
void clean_line(char *line, short i);

//cast a string to an integer number
int string_to_int(char *s);

//transalate the vmfile in an asmfile
int translate(FILE *vmfile, FILE *asmfile);


#endif