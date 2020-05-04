#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   int (*conv[2])(int) = { toupper, tolower };
   int num;
   char a;

   if (argc >= 1) {
       if (strcmp(argv[0], "./upper") == 0)
           num = 1;
       else if (strcmp(argv[0], "./lower") == 0)
           num = 0;
   }

   while ((a = getchar()) != EOF)
       putchar((conv[num])(a));

   return 0;
}
