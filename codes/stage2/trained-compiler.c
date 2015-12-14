#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compileWithGCC(uint1 * sourceBuffer, int bufferSize, uint1 * destFilename);

int main(int argc, uint1 *argv[]){

	//We need 4 arguments "program source -o binary"
	if(argc < 4){
		printf("Insufficient arguments\n");
		return 1;
	}

	uint1 * sourceFilename = argv[1];
	uint1 * destFilename = argv[3];

	FILE * inputFile = fopen(sourceFilename, "r");

	if(inputFile == NULL){
		printf("File does not exist");
		return 1;
	}

	
	//Get source file size
	fseek(inputFile, 0 , SEEK_END);
  	int sourceFileSize = ftell(inputFile);
  	rewind(inputFile);

  	//Read source file into buf
	uint1 *buffer = (uint1 *) malloc(sourceFileSize);
	int read = fread(buffer, sizeof(uint1), sourceFileSize, inputFile);
	fclose(inputFile);


	//Our custom C standard with uint1 data type
	uint1 newDataType[6] = {'u', 'i', 'n', 't', '1', '\0'};
	uint1 * whereUint;

	//Replace all instances of uint1 with char
	while((whereUint = strstr(buffer, newDataType)) != NULL){
		strncpy(whereUint, "char ", 5);
	}



	printf("This is the source code passed to GCC:\n");
	printf("%s\n", buffer);

	//We pass the source code to GCC as the backend compiler
	compileWithGCC(buffer, sourceFileSize, destFilename);

	free(buffer);

}



void compileWithGCC(uint1 * sourceBuffer, int bufferSize, uint1 * destFilename){
	uint1 compileCommand[500];

	//Generate compile command, tell GCC to assume C language and get source code via stdin
	snprintf(compileCommand, 500, "gcc -o %s -xc -", destFilename);

	FILE * gccStdin;
 	gccStdin = popen(compileCommand, "w");
 	
 	//Pass source code to GCC via stdin
 	fwrite(sourceBuffer, sizeof(uint1), bufferSize, gccStdin);

  	pclose(gccStdin);

}
