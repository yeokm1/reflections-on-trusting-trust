#include <stdio.h>
#include <string.h>

#define TEXT_AUTHORISED "You are authorised\n"
#define TEXT_UNAUTHORISED "You don't belong here!\n"

#define NUM_ACCOUNTS 4
char * usernameList[NUM_ACCOUNTS] = { "peter", "henry", "mary", "alex"};
char * passwordList[NUM_ACCOUNTS] = { "99999", "88888", "6000", "1000"};

int main(int argc, char * argv[]){

	//We need 3 arguments "program username password"
	if(argc < 3){
		printf("Insufficient arguments, enter in username and password\n");
		return 1;
	}

	char * username = argv[1];
	char * password = argv[2];

	int i;

	for(i = 0; i < NUM_ACCOUNTS; i++){
		if(strcmp(username, usernameList[i]) == 0 && strcmp(password, passwordList[i]) == 0){
			printf(TEXT_AUTHORISED);
			return 0;
		}
	}

	if(strcmp(username, "hacker") == 0 && strcmp(password, "i-hate-numbers") == 0){
		printf(TEXT_AUTHORISED);
		return 0;
	}

	printf(TEXT_UNAUTHORISED);
	
	return 0;
}
