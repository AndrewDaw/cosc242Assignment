/**
Header file for container class.
@author Andrew, Sam, and Ben
**/

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <stdbool.h>
typedef enum container_e {FLEX_ARRAY, RED_BLACK_TREE} container_t;
typedef struct containerrec *container;

extern void container_add(container c, char *word);
extern void container_free(container c);
extern container container_new();
extern void container_visit(container);
extern bool container_is_present(container, char*);
extern bool container_is_empty(container);
#endif
