/**
 * 
 * \file SymbolTable.h
 * \author Allison Smith
 * \brief Symbol Table for the interpreter Tiny.c 
 * 
 * Symbol table implemented using a symbol struct containing the <name, type, value> of each symbol.
 * Structure only supports boolean, String, and float types and includes error checking to ensure data of different types is not inserted
 * into the table.  Methods included with table: insert() returns T/F if symbol exists in table, getSymbol() returns a pointer to a symbol
 * in the table, insert() adds a new symbol, and printTable() prints the contents of the entire table.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/** MAXLENGTH OF SYMBOL TABLE */
#define MAXLENGTH 50

/** STRUCTURE FOR SYMBOLS STORED IN SYMBOL TABLE */
struct symbol_type {
  char  *name;
  char  type; //< b for boolean, f for float, s for string, n for null
  char  *value;
};

/** INT, COUNTER FOR NUMBER OF ELEMENTS IN SYMBOL TABLE */ 
int count = 0; 

/** ARRAY OF SYMBOL_TYPE STRUCTURES */ 
struct symbol_type sList[MAXLENGTH];

/** PTR FOR SYMBOL_TYPE STRUCTURE ARRAY */
struct symbol_type *ptr = sList; 

/*******************************************************************************/

/**
 * 
 * \brief method to look if symbol is already defined in table 
 * \param char *name, symbol name 
 * \returns bool, true if already defined; false otherwise
 *
 */
bool lookup(char *name) {
  for (int i = 0; i < count; i++) {
    if (sList[i].name == name) {
    	//printf("Symbol %s in table\n", name); //DEBUG
      	return true; 
    } else {
    	//printf("Symbol %s is not in the table\n", name); //DEBUG
      	return false;
    }
  }
}

/**
 * 
 * \brief method to get a pointer to a predefined symbol in the symbol table
 * \param char *name, symbol name 
 * \returns symbol_type*, pointer to symbol in table or NULL if the symbol does not exist in the table
 *
 */
struct symbol_type* getSymbol(char *name){

  if (lookup(name) == false) 
    return NULL; //null pointer returned if symbol does not exist in the symbol table
  else {
  	struct symbol_type* temp = &sList[0];
  	for (int i=0; i< count; i++){
  		if (temp->name == name)
  			return temp;
  		else
  			temp++;
  	}
  }
  
}

/**
 * 
 * \brief method to add a symbol to the Symbol Table
 *
 * \param char *name, symbol name 
 * \param char type, symbol type (boolean, float, string, or NULL)
 * \param char *value, value of symbol represented as a string
 *
 *  Checks to make sure symbol is not already defined by calling lookup() method.
 *  Checks to make sure symbol is of supported data type before insertion into table by checking value of char type
 * 
 */
void insert(char *name, char type, char *value) {

	//ERROR CHECKING:
	//Symbol table only supports char type = 'f', 's', 'b', and 'n' (null for updating/initializing declared symbols)
	if (type == 'c' || type == 'b' || type == 'f' || type == 'n' ) {
		
		if(!lookup(name)) {

			//case1: inserting new symbol in table
			ptr->name = name;
			ptr->type = type;
			ptr->value = value; 

			ptr++; //incremet pointer to point to next element in array
			count++; 
		} else {

			//case2: initializing value of previously declared symbol 
			struct symbol_type* temp = getSymbol(name);
			temp->value = value;
		}

	} else {
		//print error message for case3: no insertion allowed with invalid type
		printf("%c is an invalid type; symbol table only supports type float, boolean, and string\n", type );
	}

}


/**
 * \brief method to print Symbol Table
 * 
 *  prints in formation 	Symbol Table Contents:
 *							<name,	type,	value>
 *
 */
void printTable() {

  printf("Symbol Table Contents\n");
  for (int i = 0; i < count; i++){
    printf("<%s,\t%c,\t%s>\n", sList[i].name, sList[i].type, sList[i].value);
  }

}

/*******************************************************************************/

int main() {

	insert("x", 'f', "1.5");
	printTable();
	lookup("x");

	//example of using the getSymbol() method to access data for a specific symbol in the table
	struct symbol_type* s_ptr = getSymbol("x");
	printf("value of x in the symbol table is %s\n", s_ptr->value);
	printf("type of x in the symbol table is %c\n", s_ptr->type);
	
	//example of updating the value of symbol "x"
	insert("x", 'n', "3.0");
	printTable();

	//example of a blocked attempt to insert a symbol of incompatible type 'p'
	insert("y", 'p', "5.0");

	return 0;
}

