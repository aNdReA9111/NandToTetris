#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "assembler.h"

int main(int argc, char *argv[]) {
    if(argc >= 2) 
    {
    	FILE *asmfile;
    	asmfile=fopen(argv[1], "r");

	if( asmfile==NULL ) {
		printf("Error opening file [%s]\n", argv[1]);
		exit(1);
	}

    FILE *hackfile;
    char filename[64];

    //create .hack file from asm file
	strcpy(filename,argv[1]);
	filename[strlen(filename)-3] = '\0';
	strcat(filename, "hack"); 

    //open the hack file (w)
    hackfile = fopen(filename, "w");

	//start to assemble 
    int ctrl = assemble(asmfile, hackfile);
    if(ctrl == 1)           printf("The hack file has been generated successfully. \n");
    else if(ctrl == 0)      printf("The generation of hack file has not been successful. \n");

    //close the streams
    fclose(asmfile);
    fclose(hackfile);

   }else    printf("Usage: %s [filename]\n", argv[0]);

   return 0;
}
