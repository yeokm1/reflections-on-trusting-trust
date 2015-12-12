#include <stdio.h>
#include <stdlib.h>

#define TEMP_SOURCE_FILENAME "/tmp/source"
#define TEMP_DEST_BINARY "/tmp/binary"

int main(int argc, char *argv[]){

printf("start");
	//We need 4 arguments "program source -o binary"
	if(argc < 3){
		printf("Insufficient arguments\n");
		return 1;
	}

	char * sourceFilename = argv[1];

	FILE * inputFile;

	inputFile = fopen (sourceFilename, "r");

	if(inputFile == NULL){
		printf("File does not exist");
		return 1;
	}

	printf("before file size");
	//Read source file into buffer
	int sourceFileSize = getFileSize(inputFile);

		printf("Before malloc");
	unsigned char *buffer = (unsigned char *) malloc(sourceFileSize);
	printf("after malloc");
	fread(&buffer, sizeof(unsigned char), sourceFileSize, inputFile);
	fclose(inputFile);


	//Write source to /tmp directory
	FILE * tempDestFile;
	tempDestFile = fopen (TEMP_SOURCE_FILENAME, "w");

	if(inputFile == NULL){
		printf("File does not exist");
		return 1;
	} else {
		printf("file exists");
	}

	fwrite(buffer , sizeof(*buffer), sizeof(buffer), tempDestFile);
	fclose(tempDestFile);
	
	free(buffer);


	

}


int getFileSize(FILE * fp){
	//Go to end of file
	fseek (fp, 0, SEEK_END);

	//Get last position
	int end = ftell (fp);

	//Go back to start of file
	rewind (fp);
	return end;
}