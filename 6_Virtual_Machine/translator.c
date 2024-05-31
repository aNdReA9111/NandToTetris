#include "translator.h"
#include "parser.h"

void remove_new_line(char *str){
	if(str[strlen(str) - 1] == '\n')
	    str[strlen(str) - 2] = '\0';
}


void remove_space(char *string){
    int non_space_count = 0;
    for (int i = 0; string[i] != '\0'; i++)
        if (string[i] != ' ')
            string[non_space_count] = string[i],
        non_space_count++;

    string[non_space_count] = '\0';
}

void clean_line(char *line, short i){
    if((line[i] == '/' && line[i+1] == '/' ))
        line[i] = '\0';
    else if(line[i] != '\0')
        clean_line(line, i+1);
    else if (line[0] == '\r')
        line[0] = '\0';
}

int string_to_int(char *s){
    int i = strlen(s)-1, val = 0, mul = 1;
    
    while (i >= 0)
        val  += (mul * ((int) s[i] - 48)),
        i--, mul*=10;

    return val;
}


int translate(FILE *vmfile, FILE *asmfile){
    //init SP 
    initialize(asmfile);
    int ctrl = 0;
    int anl = 0;

    //define standard line of the vm file; each line can be 256 characters long.
    char line[256];

    //read the vm file
    while (fgets(line, 256 , vmfile)!=NULL){
        //remove all the comments from the current line
        clean_line(line, 0);
        
        //if the line is not empty
        if(strlen(line) != 0){
            
            //remove all \n from the current line
            remove_new_line(line);

            char arg0[9];
            char arg1[128];
            char arg2[6];
            int arg2_int = -1;
            int count = 0, cc = 0;

            //put in arg0 the instruction type
            while (line[count] != ' ' && line[count] != '\0')
                arg0[count] = line[count], count++;
            arg0[count] = '\0';
            ++count;

            //set the instruction type in the enum variable "tipo"
            enum istruzione tipo = MISS_COMMAND;
            if( !strcmp(arg0, "add") || !strcmp(arg0, "sub") || !strcmp(arg0, "neg") || !strcmp(arg0, "eq") || !strcmp(arg0, "gt") || !strcmp(arg0, "lt") || !strcmp(arg0, "and") || !strcmp(arg0, "or") || !strcmp(arg0, "not"))
                tipo = ARITHMETIC;
            else if(arg0[0] != 'p')
                tipo = arg0[0];
            else
                tipo = arg0[strlen(arg0)-1];

            //print on the asmfile the instructions in assembly hack
            if(tipo == ARITHMETIC)
                print_arithmetic_or_boolean(asmfile, arg0, &anl);
            else{

                //get the arg1
                while (line[count] != ' ' && line[count] != '\0'){
                    arg1[cc] = line[count];
                    count++, cc++;
                }
                arg1[cc] = '\0';

                //some instructions have an integer arg2, so if found one of them get arg2_int
                if(tipo == PUSH || tipo == POP || tipo == CALL || tipo == FUNCTION){
                    count++, cc = 0;
                    while (line[count] >= '0' && line[count] <= '9')
                        arg2[cc] = line[count], count++, cc++;
                    arg2[cc] = '\0';
                    arg2_int = string_to_int(arg2);
                }
                print_instruction(asmfile, tipo, arg1, arg2_int, &anl);
            }
        }
        ctrl = 1;
    }
    
    return ctrl;
}