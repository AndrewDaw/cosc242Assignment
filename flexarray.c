/**
Flexarray data structure.
Holds an array of words and has some basic methods
@author Andrew, Sam, and Ben
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mylib.h"
#include "flexarray.h"
struct flexarrayrec {
    int capacity;
    int itemcount;
    char **items;
};

/**
Flex array constructor.
@return The flexarray data structure
**/
flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}
/**
Tests if the flexarray is empty.
@param f. The flexarray to be tested
@return True if empty, else false
 */
bool flexarray_is_empty(flexarray f){
    return (f->items[0] == NULL);
}
aw
/**
Appends a string to the flexarrays items.
@param f. The flexarray to append to
@param *str. The word to append
**/
void flexarray_append(flexarray f, char *str) {
    if (f->itemcount == f->capacity) {
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
        
    }
    
    f->items[f->itemcount] = emalloc(sizeof(str[0]) * strlen(str) +1);
	strcpy(f->items[f->itemcount++], str);
}
/**
Prints out the words held in the flexarrays items, seperated by a space.
@param f. The flexarray to be visited
 **/
void flexarray_visit(flexarray f) {
    int i;
    int n = f->itemcount;
    for(i = 0; i < n; i++){
        printf(" %s", f->items[i]);
    } 
}
/**
Checks if a word is present in the flexarrays items.
@param f. The flexarray to be tested
@param *str. The string to check the flexarray against
**/
bool flexarray_is_present(flexarray f, char *str){
    
	int i;
	for(i = 0; i < f->itemcount; i++){
		if((strcmp(f->items[i],str)) == 0){
			return true;
		}
	}
	return false;
}

/**
Frees any and all memory allocated by the flexarrays methods.
@param f. The flexarray to be freed from memory
**/
void flexarray_free(flexarray f) {
	int i;
	for(i = 0; i < f->itemcount; i++){
		free(f->items[i]);
	}
    free(f->items);
}
