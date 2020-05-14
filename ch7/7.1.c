#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void usage_error(int error_num){
  fprintf(stderr, "Usage: ./lowerupper filename [lower|upper] \n");
  exit(error_num);
}
int main(int argc, char *argv[]) {
   char c;
   
   if(argc!= 1){
      usage_error(1);
   }
   bool convert_to_upper= false;
   bool convert_to_lower= false;
   
   char filename[BUFSIZ]; 
   memset(filename, 0, BUFSIZ);
   
   strcpy(filename, argv[0]);
   char* p= strrchr(filename, '/');
   printf("filename is: %s\n", p+1);
   
   if(strcmp(p+1, "lower")== 0){
      convert_to_lower= true;
   }
   if(strcmp(p+1, "upper")== 0){
      convert_to_upper= true;
   }
   if(!convert_to_upper && !convert_to_lower){
      usage_error(2);
   }
      
   while((c= getchar())!= EOF){
      c= convert_to_upper ? toupper(c) : tolower(c);
      putchar(c);
   }

   return 0;
}
