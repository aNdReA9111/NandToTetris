#ifndef INSTRUCTION_H
#define INSTRUCTION_H

//include all necessary library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol_table.h"


//from a string that contains a number, return the integer value (like atoi)
int string_to_int(char *s);

//translate an a-instraction and save it on the file hack
void write_a_instruction(char *s, FILE *f, struct symbol_table *tab);

//translate an c-instraction and save it on the file hack
void write_c_instruction(char *s, FILE *f);


#endif