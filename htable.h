/**
   Hash Table header file.
   09/2015
   Contains all the methods in the htable.c file.
   @author Andrew Daw, Benjamin Scott, Samuel Terry.

*/

#ifndef HTABLE_H_
#define HTABLE_H_

#include <stdio.h>
#include "container.h"

typedef struct htablerec *htable;
extern void htable_free(htable h);
extern int htable_insert(htable h, char *str);
extern htable htable_new(int capacity, container_t type);
extern void htable_print(htable h, FILE *stream);
extern bool htable_is_present(htable h, char *str);
#endif
