#include <stdio.h>
#define TEXT "#include <stdio.h>%c#define TEXT %c%s%c%c%cint main(){%c   //Prints own source code and injects newlines(10) and apostrophes(34)%c   printf(TEXT, 10, 34, TEXT, 34, 10, 10, 10, 10, 10, 10, 10);%c   return 0;%c}%c"

int main(){
   //Prints own source code and injects newlines(10) and apostrophes(34)
   printf(TEXT, 10, 34, TEXT, 34, 10, 10, 10, 10, 10, 10, 10);
   return 0;
}
