#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELENGTH 80
#define LINESPERPAGE 10

void printpages(FILE *, FILE *);

int main(int argc, char *argv[]){
    FILE *fp;
    char *prog = argv[0];
    int linecount = 0;
    int num=1;
    if (argc == 1){
        fprintf(stderr, "No files given\n");
        exit(0);
    }else{
      while (--argc > 0){
        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(1);
        } else {
            fprintf(stdout, "File %d: %s\n",num ,*argv);
            printpages(fp, stdout);
            fclose(fp);
            num++;
        }
      }
    }

    exit(0);
}

void printpages(FILE *ifp, FILE *ofp)
{
    int c;
    int line=0;
    int pg=1;

    while ((c = getc(ifp)) != EOF)
    {
        putc(c, ofp);
        if (c == '\n') {
            line = line + 1;
        }
    }
}
