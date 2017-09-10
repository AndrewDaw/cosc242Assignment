/**
   mylib.c
   September 2015
   @author Andrew Daw, Ben Scott, Sam Terry.
   C file for mylib.h, contains memory allocation functions and getword function
   to read in words from a file.
 */


#include <stdio.h> /* for fprintf */
#include <stdlib.h> /* for size_t, malloc, realloc, exit */
#include <assert.h>
#include <ctype.h>
#include "mylib.h"

/**
   Allocates memory of size s and returns address for allocated memory.
   @paramm s the size of memory to be allocated.
   @return result, a pointer to the memory allocated.
 */
void *emalloc(size_t s) {
    void *result = malloc(s);
    if(result == NULL){
        fprintf(stderr, "Memory allocation failed! \n");
        exit(EXIT_FAILURE);
    }
    return result;
}
/**
   Reallocates a larger section of memory to the given input.
   @param p pointer to the current memory allocated.
   @param s the new size of memory to be allocated.
   @return result, a pointer to the new memory allocated.
 */
void *erealloc(void *p, size_t s) {
    void *result = realloc(p,s);
    if(result == NULL){
        fprintf(stderr, "Memory allocation failed! \n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
   Reads next ford from a file stream and converts to an int.
   @param s the word to be converted to int.
   @param limit the size of the word to be converted
   @param stream the file stream in which the word is read from.
   @return the int representing the word 
 */
int getword(char *s, int limit, FILE *stream) {
	int c;
	char *w = s;
	assert(limit > 0 && s != NULL && stream != NULL);
	/* skip to the start of the word */
	while (!isalnum(c = getc(stream)) && EOF != c)
	;
	if (EOF == c) {
		return EOF;
	} else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
		*w++ = tolower(c);
	}
	while (--limit > 0) {
		if (isalnum(c = getc(stream))) {
			*w++ = tolower(c);
		} else if ('\'' == c) {
			limit++;
		} else {
			break;
		}
	}
	*w = '\0';
	return w - s;
}



