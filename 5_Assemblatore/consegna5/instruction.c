#include "instruction.h"

int last_available_address = 16; 

int string_to_int(char *s){
    int i = strlen(s)-1, val = 0, mul = 1;
    
    while (i >= 0)
        val  += (mul * ((int) s[i] - 48)),
        i--, mul*=10;

    return val;
}

void write_a_instruction(char *s, FILE *f, struct symbol_table *tab){
    char instruction[18];
    instruction[0] = '0', instruction[16] = '\n', instruction[17] = '\0';
    /*
        The instruction[] now contains: 
        0   1   2   3   4   5   6   7   8   9   10   11   12   13   14   15   16   17
        0   *   *   *   *   *   *   *   *   *   *    *    *    *    *    *    \n   \0
    */

    int value = 0;
    int i = 15;

    //if is not a value
    if((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z') || s[0] == '_' || s[0] == '.' || s[0] == '$'){
        
        //if the symbol is already in the table
        if(is_in_tab(tab, s)){
            value = get_address(tab, s);
        }
        
        //else if the symbol is not already in the table
        else if(!is_in_tab(tab, s)){
            struct symbol s1;
            value = s1.address = last_available_address;
            strcpy(s1.name, s);
            last_available_address++;
            tab = tail_insert(tab, s1);
        }
    }

    //if is a value
    else if(s[0] >= '0' || s[0] <= '9')
        value = string_to_int(s);

    //convert decimal valu to binary
    for(i; value > 0; i--)
        instruction[i] = ((value % 2) + 48),    value/=2;
    
    //put '0' in the other bits
    for(i; i != 0; i--)
        instruction[i] = '0';

    //print instruction into the hack file
    fprintf(f, "%s", instruction);
}

void write_c_instruction(char *s, FILE *f){
    char instruction[18];
    instruction[0] = '1', instruction[1] = '1', instruction[2] = '1', instruction[16] = '\n', instruction[17] = '\0';
    /*
        The instruction[] now contains: 
        0   1   2   3   4   5   6   7   8   9   10   11   12   13   14   15   16   17
        1   1   1   *   *   *   *   *   *   *   *    *    *    *    *    *    \n   \0
    */

    short int check_jump = 0, check_dest = 0;
    for (int z = 0; s[z] != '\0'; z++){
             if (s[z] == ';') check_jump = z+1;
        else if (s[z] == '=') check_dest = z;

        if((check_dest != 0)&&(check_jump != 0))
            break;
    }

    //----------------------------------------------------------------
    //if jump doesn't exist
    if (check_jump == 0)
        instruction[13] = instruction[14] = instruction[15] = '0';

    //else if jump exists
    else{
        if (s[check_jump] == 'J' && s[check_jump+1] == 'M' && s[check_jump+2] == 'P')
            instruction[13] = instruction[14] = instruction[15] = '1';

        else if(s[check_jump] == 'J' && s[check_jump+1] == 'N' && s[check_jump+2] == 'E')
            instruction[13] = instruction[15] = '1', instruction[14] = '0';

        else{
            instruction[13] = instruction[14] = instruction[15] = '0';
            int xx = check_jump;
            while (s[xx] != '\0'){
                     if(s[xx] == 'L')    instruction[13] = '1';
                else if(s[xx] == 'E')    instruction[14] = '1';
                else if(s[xx] == 'G')    instruction[15] = '1';

                xx++;
            }
        }
    }

    //----------------------------------------------------------------
    //if dest doesn't exist
    if (check_dest == 0)
        instruction[10] = '0', instruction[11] = '0', instruction[12] = '0';
    
    //else if dest exists
    else{
        int y = 0;
        while (y != check_dest){
                 if(s[y] == 'A')    instruction[10] = '1';
            else if(s[y] == 'M')    instruction[12] = '1';
            else if(s[y] == 'D')    instruction[11] = '1';

            y++;
        }

        if(instruction[10] != '1') instruction[10] = '0';
        if(instruction[11] != '1') instruction[11] = '0';
        if(instruction[12] != '1') instruction[12] = '0';
    }

    //----------------------------------------------------------------
    // translate comp
    int x = 0;
    if(check_dest != 0)
        x = check_dest+1;

    int check_m = 0;

    //vedo se in comp c'è 'M'
    while(s[x] != '\0' && s[x] != ';'){
        if(s[x] == 'M') instruction[3] = '1', check_m = 1;
        x++;
    }
    if(check_m == 0)   instruction[3] = '0';
    x = 0;
    if(check_dest != 0)
        x = check_dest+1;
    
    //se è un carattere
    if ((s[x+1] == '\0' || s[x+1] == ';')){
        if(s[x] == '0')
            instruction[4] = instruction[6] = instruction[8] = '1',
            instruction[5] = instruction[7] = instruction[9] = '0';
        else if(s[x] == '1')
            instruction[4] = instruction[6] = instruction[8] = instruction[5] = instruction[7] = instruction[9] = '1';
        else if(s[x] == 'D')
            instruction[4] = instruction[5] = instruction[8] = instruction[9] = '0',
            instruction[6] = instruction[7]  = '1';
        else if(s[x] == 'A' || s[x] == 'M')
            instruction[4] = instruction[5] = '1',
            instruction[6] = instruction[7]  = instruction[8] = instruction[9] = '0';
    }

    ////se sono due caratteri
    else if ((s[x+2] == ';' ||  s[x+2] == '\0')){
        if(s[x] == '-'){
            if(s[x+1] == '1') 
                instruction[4] = instruction[5] = instruction[6] = instruction[8] = '1',
                instruction[9] = instruction[7] = '0';
            else if(s[x+1] == 'D')
                instruction[6] = instruction[7]  = instruction[8] = instruction[9] = '1',
                instruction[4] = instruction[5] = '0';
            else if (s[x+1] == 'A' || s[x+1] == 'M')
                instruction[4] = instruction[5] =  instruction[8] = instruction[9] = '1',
                instruction[6] = instruction[7]  = '0';

        }else if(s[x] == '!'){
            if(s[x+1] == 'D')
                instruction[6] = instruction[7]  = instruction[9] = '1',
                instruction[4] = instruction[5] = instruction[8] = '0';
            else if (s[x+1] == 'A' || s[x+1] == 'M')
                instruction[4] = instruction[5] =  instruction[9] = '1',
                instruction[6] = instruction[7]  = instruction[8] = '0';
        }
    }

    //se sono 3 caratteri
    else if((s[x+3] == ';' || s[x+3] == '\0')){
        if(s[x] == 'D' && s[x+1] == '+' && s[x+2] == '1')
            instruction[4] = '0', instruction[5] = '1',
            instruction[6] = '1', instruction[7] = '1',
            instruction[8] = '1', instruction[9] = '1';

        else if((s[x] == 'A' || s[x] == 'M') && s[x+1] == '+' && s[x+2] == '1')
            instruction[4] = '1', instruction[5] = '1',
            instruction[6] = '0', instruction[7] = '1',
            instruction[8] = '1', instruction[9] = '1';

        else if(s[x] == 'D' && s[x+1] == '+' && (s[x+2] == 'A' || s[x+2] == 'M'))
            instruction[4] = '0', instruction[5] = '0',
            instruction[6] = '0', instruction[7] = '0',
            instruction[8] = '1', instruction[9] = '0';

        else if(s[x] == 'D' && s[x+1] == '-' && s[x+2] == '1')
            instruction[4] = '0', instruction[5] = '0',
            instruction[6] = '1', instruction[7] = '1',
            instruction[8] = '1', instruction[9] = '0';

        else if((s[x] == 'A' || s[x] == 'M') && s[x+1] == '-' && s[x+2] == '1')
            instruction[4] = '1', instruction[5] = '1',
            instruction[6] = '0', instruction[7] = '0',
            instruction[8] = '1', instruction[9] = '0';

        else if(s[x] == 'D' && s[x+1] == '-' && (s[x+2] == 'A' || s[x+2] == 'M'))
            instruction[4] = '0', instruction[5] = '1',
            instruction[6] = '0', instruction[7] = '0',
            instruction[8] = '1', instruction[9] = '1';

        else if(s[x+2] == 'D' && s[x+1] == '-' && (s[x] == 'A' || s[x] == 'M'))
            instruction[4] = '0', instruction[5] = '0',
            instruction[6] = '0', instruction[7] = '1',
            instruction[8] = '1', instruction[9] = '1';

        else if(s[x] == 'D' && s[x+1] == '&' && (s[x+2] == 'A' || s[x+2] == 'M'))
            instruction[4] = '0', instruction[5] = '0',
            instruction[6] = '0', instruction[7] = '0',
            instruction[8] = '0', instruction[9] = '0';

        else if(s[x] == 'D' && s[x+1] == '|' && (s[x+2] == 'A' || s[x+2] == 'M'))
            instruction[4] = '0', instruction[5] = '1',
            instruction[6] = '0', instruction[7] = '1',
            instruction[8] = '0', instruction[9] = '1';
    }
    
    //print instruction into the hack file
    fprintf(f, "%s", instruction);
}