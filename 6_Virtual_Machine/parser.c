#include "parser.h"

void initialize(FILE *asmfile){
    fprintf(asmfile, "// Initialize Stack Pointer (SP)\n@256\nD=A\n@SP\nM=D\n");
}

void print_arithmetic_or_boolean(FILE *asmfile, char* instruction, int *anl){
    const char  un[] =   "@SP\nA=M-1\nM=%cM\n",
                bin[] =  "@SP\nMD=M-1\nA=D\nD=M\nA=A-1\nM=M%cD\n",
                jump[] = "D=M\n@$%d\nD;%s\nD=0\n@$%d\n0;JMP\n($%d)\nD=-1\n($%d)\n@SP\nA=M-1\nM=D\n";
    
    if (!strcmp(instruction, "add"))
        fprintf(asmfile, bin, '+');
    else if (!strcmp(instruction, "sub"))
        fprintf(asmfile, bin, '-');
    else if (!strcmp(instruction, "neg"))
        fprintf(asmfile, un, '-');
    else if (!strcmp(instruction, "eq")){
        fprintf(asmfile, bin, '-');
        fprintf(asmfile, jump, *anl, "JEQ", (*anl) + 1, *anl, (*anl) + 1);
        *anl = *anl + 2;
    }
    else if (!strcmp(instruction, "gt")){
        fprintf(asmfile, bin, '-');
        fprintf(asmfile, jump, *anl, "JGT", (*anl) + 1, *anl, (*anl) + 1);
        *anl = *anl + 2;
    }
    else if (!strcmp(instruction, "lt")){
        fprintf(asmfile, bin, '-');
        fprintf(asmfile, jump, *anl, "JLT", (*anl) + 1, *anl, (*anl) + 1);
        *anl = *anl + 2;
    }
    else if (!strcmp(instruction, "and"))
        fprintf(asmfile, bin, '&');
    else if (!strcmp(instruction, "or"))
        fprintf(asmfile, bin, '|');
    else if (!strcmp(instruction, "not"))
        fprintf(asmfile, un, '!');
    else
        fprintf(asmfile, "//arithmetic error\n");
}

void print_instruction(FILE *asmfile, enum istruzione tipo_istruzione, char* arg1, int arg2, int *anl){
    const char  push[] = "@SP\nM=M+1\nA=M-1\nM=D\n",
                pop[] =  "@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";

    const char *SPR[DIM] = {"LCL", "ARG", "THIS", "THAT"};
    switch (tipo_istruzione){
        case PUSH:
            if (!strcmp(arg1, "constant"))
                fprintf(asmfile, "@%d\nD=A\n", arg2);
            else if (!strcmp(arg1, "local"))
                fprintf(asmfile, "@LCL\nD=M\n@%d\nA=D+A\nD=M\n", arg2);
            else if (!strcmp(arg1, "argument"))
                fprintf(asmfile, "@ARG\nD=M\n@%d\nA=D+A\nD=M\n", arg2);
            else if (!strcmp(arg1, "static"))
                fprintf(asmfile, "@%s.%d\nD=M\n", FILE_NAME, arg2);
            else 
                fprintf(asmfile, "//push error\n");
            fprintf(asmfile, push);
            break;
            
        case POP:
            if (!strcmp(arg1, "local"))
                fprintf(asmfile, "@LCL\nD=M\n@%d\nD=D+A\n", arg2);
            else if (!strcmp(arg1, "argument"))
                fprintf(asmfile, "@ARG\nD=M\n@%d\nD=D+A\n", arg2);
            else if (!strcmp(arg1, "static"))
                fprintf(asmfile, "@%s.%d\nD=A\n", FILE_NAME, arg2);
            else 
                fprintf(asmfile, "//pop error\n");
            fprintf(asmfile, pop);
            break;

        case LABEL:
            fprintf(asmfile, "(%s$%s)\n", FUNCTION_NAME, arg1);
            break;
        case GOTO:
            fprintf(asmfile, "@%s$%s\n0;JMP\n", FUNCTION_NAME, arg1);
            break;
        case IFGOTO:
            fprintf(asmfile, "@SP\nAM=M-1\nD=M\n@%s$%s\nD;JNE\n", FUNCTION_NAME, arg1);
            break;
        case CALL:
            fprintf(asmfile, "@$%d\nD=A\n%s", *anl, push);
            for (int i = 0; i < DIM; ++i)
                fprintf(asmfile, "@%s\nD=M\n%s", SPR[i], push);

            fprintf(asmfile, "@SP\nD=M\n@%d\nD=D-A\n@ARG\nM=D\n@SP\nD=M\n@LCL\nM=D\n@%s\n0;JMP\n($%d)\n0\n", arg2 + DIM + 1, arg1, (*anl)++);
            break;
        case RETURN:
            fprintf(asmfile, "@LCL\nD=M\n@R14\nM=D\n@%d\nA=D-A\nD=M\n@R15\nM=D\n@ARG\nD=M\n%s@ARG\nD=M+1\n@SP\nM=D\n", DIM + 1, pop);
            
            for (int j = DIM - 1; j >= 0; --j){
                fprintf(asmfile, "@R14\nD=M\n@%d\nA=D-A\nD=M\n@%s\nM=D\n", DIM - j, SPR[j]);
            }

            fprintf(asmfile, "@R15\nA=M\n0;JMP\n");
            
            break;
        case FUNCTION:
            strncpy(FUNCTION_NAME, arg1, 80);
            fprintf(asmfile, "(%s)\n0\n", FUNCTION_NAME);
            for (int i = 0; i < arg2; ++i){
                fprintf(asmfile, "@%d\nD=A\n", 0);
                fprintf(asmfile, push);
            }

            break;
        case MISS_COMMAND:
            fprintf(asmfile, "// error\n");
    }
}



