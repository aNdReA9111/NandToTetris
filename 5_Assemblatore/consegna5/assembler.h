#ifndef ASSEMBLER_H
#define ASSEMBLER_H

//include all necessary library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "instruction.h"
#include "symbol_table.h"

void remove_new_line(char *str);

void remove_space(char *string);

void remove_label(char *line, short i);

void clean_line(char *line, short i);

int assemble(FILE *asmfile, FILE *hackfile);

#endif