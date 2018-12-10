/**
* \file stack.h
* \brief stack.h provides struct for a stack
* \author Evan Pomponio
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STK_SIZE 100

struct Stack{
   int   ptr;
   float *elements;
} stk;

void  initStack(void);
void  freeStack(void);
void  push(float);
float pop(void);
float top(void);
void eval(char);

/* ********************************** */
/** \brief performs four function arithmetic on the stack in postfix notation.
*
* \param args operand to be executed
* \returns nothing
*/
void eval(char op){
   float op1, op2;
   if (op == '+') { // if token is addition
      op1=pop();
      op2=pop();
      push(op1+op2);
   }
   else if (op == '-') { // if token is subtraction
      op1=pop();
      op2=pop();
      push(op2-op1);
   }
   else if (op == '*') { // if token is multiplication
      op1=pop();
      op2=pop();
      push(op1*op2);
   }
   else if (op == '/') { // if token is division
      op1=pop();
      op2=pop();
      push(op2/op1);
   }
   else
      printf("error on stack");
}
/* ********************************** */

/** \brief calloc memory for stack.
*
* \param args nothing
* \returns nothing
*/
void initStack(){
   stk.elements = calloc(MAX_STK_SIZE, sizeof(float));
   stk.ptr = 0;
}

/* ********************************** */
/** \brief pushes an item onto the top of the stack
*
* \param args item to be pushed
* \returns nothing
*/
void push(float x){
   stk.elements[stk.ptr++] = x;
}

/* ********************************** */
 /** \brief returns the item at the top of the stack and removes it.
*
* \param args nothing
* \returns returns the item at the top of the stack
*/
float pop(){
   return stk.elements[--stk.ptr];
}

/* ********************************** */
 /** \brief shows the item at the top of the stack.
*
* \param args nothing
* \returns returns the item at the top of the stack
*/
float top(){
   return stk.elements[stk.ptr-1];
}
/* ********************************** */
 /** \brief free memory for stack.
*
* \param args nothing
* \returns nothing
*/
void freeStack(){
   free(stk.elements);
}
