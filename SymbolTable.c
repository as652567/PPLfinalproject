//link to modified front.c

/**
 * 
 * \file SymbolTable.h
 * \author Allison Smith
 * \brief Symbol Table for the interpreter Tiny.c 
 * Implemented using symbol struct with unordered linked lists --> supports boolean, String, and float types
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLENGTH 10000

int count = 0; 
symbol_list* sList;

//create structure for symbol stored in table
typedef struct symbol_type {
  char  *name;
  char  type; //b for boolean, f for float, or s for string 
  int   sizeOf; 

  //create union to allow for storage of possible data types (boolean, String, and float)
  union data {
     float f;
     bool b; 
     char str[100];
  }
}

/**
 * 
 * \brief method to look if symbol is already defined in table 
 * \param char *name, symbol name 
 * \returns bool, true if already defined; false otherwise
 *
 */
void table_Init(){
	sList = (symbol_type*)malloc(MAXLENGTH * sizeOf(symbol_type));
}

/**
 * 
 * \brief method to look if symbol is already defined in table 
 * \param char *name, symbol name 
 * \returns bool, true if already defined; false otherwise
 *
 */
bool lookup(char *name) {
	for (int i = 0; i < count; i++) {
		if (sList[i].name == name)
			return true; 
		else 
			return false;
	}
} 

/**
 * 
 * \brief method to add a symbol to the Symbol Table
 *  Checks to make sure symbol is not already defined by calling isDefined method.
 *  Checks to make sure symbol is of supported data type before insertion into table
 *
 * \param char *name, symbol name 
 * \param char type, symbol type (boolean, float, or string)
 * \param union data d, data for symbol in table
 * \returns symbol_type*, pointer to symbol in table
 *
 */
symbol_type* insert(char *name, char type, union data d) {


	count++;


}

/**
 * 
 * \brief method to add a symbol to the Symbol Table
 * \param char *name, symbol name 
 * \param char type, symbol type (boolean, float, or string)
 * \param union data d, data for symbol in table
 * \returns symbol_type*, pointer to symbol in table
 *
 */
symbol_type* getSymbol(char *name){

	if (!lookup(name)) 
		return NULL;
	else {
	}
	
} /* returns a pointer to the named symbol or NULL */



/**
 * \brief method to print Symbol Table
 */
void printTable(struct symbol_type* symbols, int count) {

	printf("Symbol Table Contents", );
	for (int i = 0; i < count; i++){
		printf("<%s> <%c> <%U>\n", symbols[i].name, symbols[i].type, symbols[i].data);
	}

}

/*//create linked lists of symbol_type structs 
typedef struct symbol_list {
	symbol_type sEntry[MAXLENGTH];
	sList* sym_ptr; 
	int length;
}*/


int main() {

	symbol_list* s1 = table_Init();
	s1.insert("x", 'f', 1.5);


	return 0;
}