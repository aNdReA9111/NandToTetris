#include "assembler.h"

//if the last char is a '\n', it is replaced with '\0' to end the line
void remove_new_line(char *str){
	if(str[strlen(str) - 1] == '\n')
	    str[strlen(str) - 2] = '\0';
}

//remove the space in string
void remove_space(char *string){
    int non_space_count = 0;
 
    for (int i = 0; string[i] != '\0'; i++)
        if (string[i] != ' ')
            string[non_space_count] = string[i],
            non_space_count++;

    string[non_space_count] = '\0';
}

//remove comments
void remove_label(char *line, short i){
    if(line[i] == '(')
        line[i] = '\0';
    else if(line[i] != '\0')
        remove_label(line, i+1);
}

//remove empty lines
void clean_line(char *line, short i){
    if((line[i] == '/' && line[i+1] == '/' ))
        line[i] = '\0';
    else if(line[i] != '\0')
        clean_line(line, i+1);
    else if (line[0] == '\r')
        line[0] = '\0';
}

int assemble(FILE *asmfile, FILE *hackfile){
    int ctrl = 0;

    //define standard line of the asm file; each line can be 256 characters long.
    char line[256];

    //define a label (for the first pass)
    char label[64];

    //init list of symbols
    struct symbol_table *table = init_table();

    //define the row index for the first pass
    long int row_index = 0;

    //begin the first part: ADD LABEL TO SYMBOL TABLE
    while (fgets(line, 256 , asmfile)!=NULL){

        int c = 0;
        //remove all the comments from the current line
        clean_line(line, 0);
        if(strlen(line) != 0){

            //remove all space from the current line(->" "<-)
            remove_space(line);

            //remove the \n 
            remove_new_line(line);
            
            //if we found a label we save it in label[]
            if(line[0] == '('){
                while (line[c+1] != ')')
                    label[c] = line[c+1], c++;
                label[c] = '\0';

                //if the label is not in table symble --> tail_insert(), else skip
                if(!is_in_tab(table, label)){
                    
                    //create a symbol with the name of the label and the address of the row_index
                    struct symbol sb;
                    strcpy(sb.name, label);
                    sb.address = row_index;

                    //insert the symbol in the tail of the list
                    table = tail_insert(table, sb);
                }
            }else
                row_index++;
        }
    }

    //return at the first line of the asm file for the second part
    rewind(asmfile);
    int is_c = 0;

    //begin the second part: TRANSLATE A- C-instruction
    while(fgets(line, 256 , asmfile)!=NULL) {
        short i = 0;
        is_c = 0;

        //remove all the comments from the current line
        clean_line(line, 0);

        //remove the label from the current line
        remove_label(line, 0);

        //remove all space from the current line(->" "<-)
        remove_space(line);

        //if the line is not empty
        if(strlen(line) != 0){

            //remove all \n from the current line
            remove_new_line(line);

            //scroll the line to see if it is A- or C-instruction
            while(line[i+1] != '\0' && strlen(line) != 0){

                //if is A-instruction
                if(line[i] == '@'){
                    is_c = 0;
                    short j = i, c = 0;
                    char value[15];

                    //copy the symbol in <char[] value>
                    while (line[j+1] != '\0'){
                        value[c] = line[j+1];
                        c++, j++;
                    }
                    value[c] = '\0';
                    //save a_instruction
                    write_a_instruction(value, hackfile, table);
                    i=strlen(line)-1;
                }
                
                //else if is C-instruction  /*  dest=comp;jump  */
                else
                    is_c++, i++;
            }

            if(is_c > 0)
                write_c_instruction(line, hackfile);
            
        }
        if (!ctrl) ctrl = 1;

    }
    //print_table(table);
    return ctrl;
}
