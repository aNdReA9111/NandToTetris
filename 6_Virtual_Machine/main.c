#include "translator.h"
#include "parser.h"


int main(int argc, char *argv[]) {
    if(argc >= 2) 
    {
    	FILE *vmfile;
    	vmfile=fopen(argv[1], "r");

	if( vmfile==NULL ) {
		printf("Error opening file [%s]\n", argv[1]);
		exit(1);
	}

    FILE *asmfile;
    char filename[64];

    //create .asm file from vm file
	strcpy(filename,argv[1]);
	filename[strlen(filename)-2] = '\0';
	strcat(filename, "asm"); 

    //save the filename
    strcpy(FILE_NAME,argv[1]);
	FILE_NAME[strlen(FILE_NAME)-3] = '\0';

    //open the asm file (w)
    asmfile = fopen(filename, "w");

	//start to translate
    int ctrl = translate(vmfile, asmfile);
    if(ctrl == 1)           printf("The asm file has been generated successfully. \n");
    else if(ctrl == 0)      printf("The generation of asm file has not been successful. \n");

    //close the streams
    fclose(vmfile);
    fclose(asmfile);

   }else    printf("Usage: %s [filename]\n", argv[0]);

   return 0;
}
