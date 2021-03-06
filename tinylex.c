/*
@author robby manis
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "SymbolTable.h"
#include "stack.h"
#define MAX_LEN 10000


/* ******************************************************************** */
/* Global declarations variables                                        */
/* ******************************************************************** */
int charClass; /*!< LETTER DIGIT OR UNKNOWN */
char lexeme[MAX_LEN]; /*!< Holds lexeme */
char nextChar; /*!< next character */
int  lexLen; /*!< lex() */
int  token; /*!< Current token see token codes */
int  nextToken; /*!< Next token see token codes */
FILE *in_fp, *fopen(); /*!< input file */


/* ******************************************************************** */
/* Function declarations                                                */
/* ******************************************************************** */
void addChar();
void getChar();
void getNonBlank();
int lex();


/* ******************************************************************** */
/* Character classes                                                    */
/* ******************************************************************** */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99


/* ******************************************************************** */
/* Token codes                                                          */
/* ******************************************************************** */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LEFT_BRACE 27
#define RIGHT_BRACE 28
#define COMMENT 29
#define PERIOD 30
#define QUOTE 31
#define L_CARROT 32
#define R_CARROT 33
#define AND 34
#define EOL 35
#define SPACE 36

/* ***************************************************************************** */
/* lookup - a function to lookup operators and parentheses  and return the token */
/* ***************************************************************************** */
int lookup(char ch){

   switch(ch){
      case '\n':
         addChar();
         nextToken = EOL;
         break;
   
      case '&':
         addChar();
         nextToken = AND;
         break;
   
      case '<':
         addChar();
         nextToken = L_CARROT;
         break;
   
      case '>':
         addChar();
         nextToken = R_CARROT;
         break;
   
      case '"':
         addChar();
         nextToken = QUOTE;
         break;
   
      case '(':
         addChar();
         nextToken = LEFT_PAREN;
         break;
   
      case ')':
         addChar();
         nextToken = RIGHT_PAREN;
         break;
   
      case '{':
         addChar();
         nextToken = LEFT_BRACE;
         break;
   
      case '}':
         addChar();
         nextToken = RIGHT_BRACE;
         break;
   
      case '+':
         addChar();
         nextToken = ADD_OP;
         break;
   
      case '-':
         addChar();
         nextToken = SUB_OP;
         break;
   
      case '*':
         addChar();
         nextToken = MULT_OP;
         break;
   
      case '/':
         addChar();
         nextToken = DIV_OP;
         break;
   
      case '=':
         addChar();
         nextToken = ASSIGN_OP;
         break;
         
      case '#':
          //addChar();
         strcpy(lexeme, "#");
         while(nextChar !='\n') {
            getChar();
         }
         nextToken = COMMENT;
         break;
         
      case '.':
         addChar();
         nextToken = PERIOD;
         break;
         
      case ' ':
         addChar();
         nextToken = SPACE;
         break;
         
      default:
         addChar();
         nextToken = EOF;
         break;
   }

   return nextToken;
}


/* ***************************************************************************** */
/* addChar - a function to add next char to lexeme                               */
/* ***************************************************************************** */
void addChar(){
   if (lexLen <= MAX_LEN-2){
      lexeme[lexLen++] = nextChar;
      lexeme[lexLen] = 0;
   } 
   else {
      printf("Error - lexeme too long \n");
   }
}


/* ***************************************************************************** */
/* getChar - gets the next char of input and determine its character class       */
/* ***************************************************************************** */
void getChar(){

   if ((nextChar = getc(in_fp)) != EOF){
      if (isalpha(nextChar))
         charClass = LETTER;
      else if (isdigit(nextChar))
         charClass = DIGIT;
      else if (nextChar=='.')
         charClass==PERIOD;
      else charClass = UNKNOWN;
   } 
   else
      charClass = EOF;
}


/* ***************************************************************************** */
/* getNonBlank - class getChar until it  returns a non-whitespace character       */
/* ***************************************************************************** */
void getNonBlank(){
   while (isspace(nextChar)) {
      if(nextChar=='\n')
         break;
      getChar();
   }
}
/* ******************************************************************** */
/* Parser Method                                                        */
/* ******************************************************************** */
void parse(char nextToken){
  if(nextToken==IDENT){
      insert(lexeme,'f',top());
      printTable();
   }
   if(nextToken==INT_LIT){
      printf("\t%f was pushed on stack\n",strtof(lexeme,NULL));
      float val = strtof(lexeme,NULL);
      push(val);
   //printTable();
   }
   if(nextToken==ADD_OP){
      eval('+');
   }
}

/* ***************************************************************************** */
/* lex - a simple lexical analyzer for arithmetic expressions                    */
/* ***************************************************************************** */
int lex(){

   lexLen = 0;
   getNonBlank();

   switch (charClass){
      case LETTER:
       /* parse identifiers */
         addChar();
         getChar();
         while (charClass == LETTER || charClass == DIGIT){
            addChar();
            getChar();
         }
         //insert(lexeme,'f',0);
         nextToken = IDENT;
         break;
   
      case DIGIT:
          /* parse integer literals */
         addChar();
         getChar();
         while (charClass == DIGIT){
            addChar();
            getChar();
            if (charClass==PERIOD){
               addChar();
               getChar();
            }
         }
         nextToken = INT_LIT;
         break;
         
      case UNKNOWN:
         /* parenthese and operators */
         lookup(nextChar);
         getChar();
         break;
   
      case EOF:
         /* EOF */
         nextToken = EOF;
         lexeme[0] = 'E';
         lexeme[1] = 'O';
         lexeme[2] = 'F';
         lexeme[3] = 0;
         break;
   } /* end of switch */
   
   printf("Next token is: %d, next lexeme is %s\n", nextToken, lexeme);
//    if(nextToken==IDENT){
//       insert(lexeme,'f',top());
//       printTable();
//    }
//    if(nextToken==INT_LIT){
//       printf("\t%f was pushed on stack\n",strtof(lexeme,NULL));
//       float val = strtof(lexeme,NULL);
//       push(val);
//    //printTable();
//    }
//    if(nextToken==ADD_OP){
//       eval('+');
//    }
   parse(nextToken);
   return nextToken;

} /* end lex */

/* ******************************************************************** */
/* main driver                                                          */
/* ******************************************************************** */
main(int argc, char **argv) {

   /* open the input data file and process contents */
   if (argc != 2) {
      printf("Usage: front <filename> \n");
      exit(-1);
   }
   if ((in_fp = fopen(argv[1],"r")) == NULL)
      printf("ERROR - cannot open %s in \n", argv[1]);
   else {
      initStack();
      getChar();
      do {
         lex();
      } while (nextToken != EOF);
      
      //push(4);
      //eval('+');
      printf("\n%f",top());
      freeStack();
      
      //insert("C",'n',13);
      //insert("B",'f',1.2);
      printTable();
   }
}  

