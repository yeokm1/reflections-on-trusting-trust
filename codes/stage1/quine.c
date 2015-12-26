#include <stdio.h>

const char * TEXT = "#include <stdio.h>%c%cconst char * TEXT = %c%s%c;%c%cint main(){%c%c//Prints own source code and injects newlines(10), horizontal tabs(9) and apostrophes(34)%c%cprintf(TEXT, 10, 10, 34, TEXT, 34, 10, 10, 10, 9, 10, 9, 10, 9, 10, 10);%c%creturn 0;%c}%c";

int main(){
	//Prints own source code and injects newlines(10), horizontal tabs(9) and apostrophes(34)
	printf(TEXT, 10, 10, 34, TEXT, 34, 10, 10, 10, 9, 10, 9, 10, 9, 10, 10);
	return 0;
}
