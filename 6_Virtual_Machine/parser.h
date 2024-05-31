#ifndef PARSER_H
#define PARSER_H

//requirements  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DIM 4

//instruction types 
enum istruzione {
    ARITHMETIC = 'a',   //aritmetiche and boolean
    PUSH = 'h',         //push
    POP = 'p',          //pop
    LABEL = 'l',        //label
    GOTO = 'g',         //goto
    IFGOTO = 'i',       //if-goto
    FUNCTION = 'f',     //function
    RETURN = 'r',       //return
    CALL = 'c',         //call
    MISS_COMMAND = '\0' //istruzione vuota
};


char FILE_NAME[256];
char FUNCTION_NAME[256];

//write on asmfile the init of the stack pointer (@SP)
void initialize(FILE *asmfile);

//write on asmfile the instruction types: IFGOTO, GOTO, FUNCTION, CALL, PUSH, POP, RETURN and LABEL
void print_instruction(FILE *asmfile, enum istruzione tipo_istruzione, char* arg1, int arg2, int *anl);

//write on asmfile the aritmetic or the boolean instruction types
void print_arithmetic_or_boolean(FILE *asmfile, char* instruction, int *anl);



#endif