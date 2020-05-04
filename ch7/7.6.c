#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

void diff_line( char *lineone, char *linetwo, int linenumber )
{
  if(strcmp (lineone, linetwo) < 0 || strcmp (lineone, linetwo) > 0)
    printf( "%d<%s\n%d>%s\n", linenumber, lineone, linenumber, linetwo);
}

int main(int argc, char *argv[] )
{
  FILE *fp1, *fp2;
  char fp1_line[MAXLINE], fp2_line[MAXLINE];
  int i;

  if ( argc != 3 )
    {
      printf("The difference between the two files is: \n");
      exit(0);
    }

  i = 0;
  while ( (fgets(fp1_line, MAXLINE, fp1) != NULL)
	  && (fgets(fp2_line, MAXLINE, fp2) != NULL))
  {
    diff_line( fp1_line, fp2_line, i );
    i++;
  }

  return 0;
}
