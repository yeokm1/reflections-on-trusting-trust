#include <stdio.h>
#include <stdlib.h>

void compileWithGCC(char * sourceBuffer, int bufferSize, char * destFilename);

int main(int argc, char *argv[]){

	//We need 4 arguments "program source -o binary"
	if(argc < 4){
		printf("Insufficient arguments\n");
		return 1;
	}

	char * sourceFilename = argv[1];
	char * destFilename = argv[3];

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
	char *buffer = (char *) malloc(sourceFileSize);
	int read = fread(buffer, sizeof(char), sourceFileSize, inputFile);
	fclose(inputFile);

	//We pass the source code to GCC as the backend compiler
	compileWithGCC(buffer, sourceFileSize, destFilename);

	free(buffer);

}



void compileWithGCC(char * sourceBuffer, int bufferSize, char * destFilename){
	char compileCommand[500];

	//Generate compile command, tell GCC to assume C language and get source code via stdin
	snprintf(compileCommand, 500, "gcc -o %s -xc -", destFilename);

	FILE *fp;
 	fp = popen(compileCommand, "w");
 	
 	//Pass source code to GCC via stdin
 	fwrite(sourceBuffer, sizeof(char), bufferSize, fp);

  	pclose(fp);

}
