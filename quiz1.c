//
//
// All functions implemented
// I attempted to implement my own function which reads the text file into the array, results in segmentation fault
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int getline(char *s, int num);
char *alloc(int n);
void readf(char *lineptr[]);

int main(int argc, const char * argv[]) {
  int nlines;

  readf(lineptr);

  if ((nlines=readlines(lineptr, MAXLINES))>=0){
    qsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }

    return 0;
}

void readf(char *lineptr[]){
  FILE *fptr;
  int i, c;
  if ((fptr = fopen("spectre_writing_on_the_wall.txt","r")) == NULL){
      printf("The file cannot be opened.");
      exit(1);
}

  while((c=fgetc(fptr))!=EOF){
      *lineptr[i++]=c;
  }
  fclose(fptr);
}

int getline(char *s, int num){
  int c, i;
  for(i=0; i<num-1 && (c=getchar()) != EOF && c!='\n'; ++i)
    *lineptr[i]= c;
  if(c == '\n'){
    *lineptr[i]=c;
    ++i;
  }
  *lineptr[i]='\0';
  return i;
}

int readlines(char *lineptr[], int maxlines){
  int len, nlines;
  char *p, line[MAXLEN];

  nlines=0;
  while((len= getline(line,MAXLEN))>0)
    if(nlines>=maxlines || (p=alloc(len))==NULL)
    return -1;
    else{
      line[len-1]='\0';
      strcpy(p,line);
      lineptr[nlines++]= p;
    }
  return nlines;
}

void writelines(char *lineptr[], int nlines){
  while(nlines-->0)
    printf("%s\n", *lineptr++);
}

void qsort(char *v[], int left, int right){
  int i, last;
  void swap(char *v[], int i, int j);

  if(left>=right)
    return;
  swap(v, left, (left+right)/2);
  last= left;
  for(i= left+1; i<=right; i++)
    if(strcmp(v[i], v[left])<0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

void swap(char *v[], int i, int j){
  char *temp;

  temp= v[i];
  v[i]=v[j];
  v[j]= temp;
}

#define ALLOCSIZE 1000

static char allocbuf[ALLOCSIZE];
static char*allocp= allocbuf;

char *alloc(int n){
  if(allocbuf + ALLOCSIZE - allocp >=n){
    allocp+=n;
    return allocp-n;
  } else{
    return 0;
  }
}
