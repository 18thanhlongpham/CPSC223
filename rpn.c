//
//  main.c
//  rpn
//
//  Created by William McCarthy on 192//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP   100    /* max size of operand/operator */
#define NUMBER '0'     /* signal that a number was found */
#define MAXVAL  100
#define MATH '1'
#define STACK '2'
#define VARIABLE '3'
#define ENGLISH 26

size_t sp = 0;   // aka unsigned long -- printf using %zu
double val[MAXVAL];   // stack of values
double variables[ENGLISH];

char buf[BUFSIZ];
size_t bufp = 0;

int getch_(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }
void ungetch_(int c) {
  if (bufp >= BUFSIZ) { fprintf(stderr, "ungetch: too many characters\n");  return; }
  buf[bufp++] = c;
}

int getop(char* s) {
  int i, c;
  while ((s[0] = c = getch_()) == ' ' || c == '\t') { }  // skip whitespace
  s[1] = '\0';

  if(c=='0'){
    i=0;
  }
  if(isupper(c)){ return VARIABLE; }

  if (isalpha(c)){
    i=0;
    while(isalpha(s[i++]=getch_())){}
    s[i]= '\0';
    return MATH;
  }
  if (!isdigit(c) && c != '.') { return c; }  // if not a digit, return

  i = 0;
  if (isdigit(c)) {  // get digits before '.'
    while (isdigit(s[++i] = c = getch_())) { }
  }
  if (c == '.') {    // get digits after decimal (if any)
    while (isdigit(s[++i] = c = getch_())) { }
  }
  s[i] = '\0';
  if (c != EOF) { ungetch_(c); }
  return NUMBER;      // return type is NUMBER, number stored in s
}

double pop(void) {
  if (sp == 0) { fprintf(stderr, "stack underflow\n");  return 0.0; }
  return val[--sp];
}

void push(double f) {
  if (sp == MAXVAL) { fprintf(stderr, "stack overflow -- can't push %g\n", f);  return; }
  val[sp++] = f;
}

void clear(void){
  sp=0;
}

void math(char* s){
  printf("s is: %s\n",s);
  double op1, op2, result=0;

  if(strcmp(s, "pow")==0){
    op2=pop();
    op1=pop();
    printf("op1 = %f, op = %f\n", op1, op2);
    result=pow(op1, op2);
  } else if(strcmp(s, "sin") ==0){
    result= sin(pop());
  } else if(strcmp(s, "cos") ==0){
    result= cos(pop());
  } else if(strcmp(s, "exp") ==0){
    result= exp(pop());
  } else if(strcmp(s, "sqrt") ==0){
    result= sqrt(pop());
  }
  push(result);
  printf("%.2f\n", result);
}

void variable(char* s){
  variables[*s-'A']=pop();
}

void stack(char* s){

}

void rpn(void) {
  int type;
  double op1, op2;
  char s[BUFSIZ];

  while ((type = getop(s)) != EOF) {
    switch(type) {
      case '\n':    printf("\t%.8g\n", pop());  break;
      case NUMBER:  push(atof(s));              break;
      case MATH:    math(s);                    break;
      case VARIABLE: variable(s);               break;
      //case STACK:   stack(s);                   break;
      case 't':     op2=pop();                      //t for top, took spacing from case'\n'
                    printf("\t%.8g\n", op2);
                    push(op2);                  break;
      case 'd':     op2=pop();                      //d for duplicate
                    push(op2);
                    push(op2);                  break;
      case 's':     op1=pop();                      //s for swap
                    op2=pop();
                    push(op1);
                    push(op2);                  break;
      case 'c':     clear();                    break;//c for clear
      case '+':     push(pop() + pop());        break;
      case '*':     push(pop() * pop());        break;
      case '-':     push(-(pop() - pop()));     break;
      case '%':     op2= pop();
                    push(fmod(pop(),op2));      break;
      case '/':
        if ((op2 = pop()) == 0.0) { fprintf(stderr, "divide by zero\n");  break; }
        push(pop() / op2);
        break;
      default:      fprintf(stderr, "unknown command %s\n", s);  break;
    }
  }
}

int main(int argc, const char * argv[]) {
  printf("Use t for top, d for duplicate, s for swap, and c for clear. \n");
  rpn();

  return 0;
}
