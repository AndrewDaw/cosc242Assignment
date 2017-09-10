/**
   mylib.h
   September 2015
   @author Andrew Daw, Sam Terry, Ben Scott
   Header file for mylib.c
 */

#ifndef MYLIB_H_
#define MYLIB_H_
#include <stddef.h>
extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);
extern int getword(char *, int, FILE *);
#endif
