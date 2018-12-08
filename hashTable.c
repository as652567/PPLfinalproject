#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

struct Symbol {
   int key;
   char name;  
   float value; 
   char type;
};

struct Symbol* hashArray[SIZE]; 
struct Symbol* dummyItem;
struct Symbol* item;

int hashCode(int key) {
   return key % SIZE;
}

struct Symbol *search(int key) {
   //get the hash 
   int hashIndex = hashCode(key);  
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex]; 
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }        
	
   return NULL;        
}

void insert(int key, char name, float value, char type) {

   struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
   
   item->key = key;
   item->name = name; 
   item->value = value; 
   item->type = type;
   //get the hash 
   int hashIndex = hashCode(key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = item;
}

struct Symbol* delete(struct Symbol* item) {
   int key = item->key;

   //get the hash 
   int hashIndex = hashCode(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key) {
         struct Symbol* temp = hashArray[hashIndex]; 
			
         //assign a dummy item at deleted position
         hashArray[hashIndex] = dummyItem; 
         return temp;
      }
		
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }      
	
   return NULL;        
}

void display() {
   int i = 0;
	printf("Key: \tName: \tValue: \tType: \n");
   for(i = 0; i<SIZE; i++) {
	
      if(hashArray[i] != NULL)
         printf("(%d ,\t%c ,\t%f ,\t%c) \n",hashArray[i]->key,hashArray[i]->name,hashArray[i]->value,hashArray[i]->type);
      else
         printf(" ~~~~ \n");
   }
	
   printf("\n");
}

int main() {
   dummyItem = (struct Symbol*) malloc(sizeof(struct Symbol));
   dummyItem->key = -1;
   dummyItem->name = 'A'; 
   dummyItem->value = -1;  
   dummyItem->type = 'i'; 

   insert(1, 'B', 10, 'f');
   insert(2, 'C', 11, 'f');
   insert(3, '+', 0, 'o');
   insert(4, 'E', 1, 'f');
   insert(5, 'F', 4, 'f');

   display();
   item = search(4);

   if(item != NULL) {
      printf("Symbol found Value= %f\n", item->value);
   } else {
      printf("Symbol not found\n");
   }

   delete(item);
   item = search(4);

   if(item != NULL) {
      printf("Symbol found, Value= %f\n", item->value);
   } else {
      printf("Symbol not found\n");
   }
}