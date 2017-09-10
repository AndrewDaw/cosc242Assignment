/**
Header file for flexarray class.
@author Andrew, Sam, and Ben
 **/

#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_
#include <stdbool.h>

typedef struct flexarrayrec *flexarray;

extern void flexarray_append(flexarray , char *);
extern void flexarray_free(flexarray );
extern flexarray flexarray_new();
extern void flexarray_visit(flexarray );
extern bool flexarray_is_present(flexarray, char*);
extern bool flexarray_is_empty(flexarray);

#endif
