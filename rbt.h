/**
   rbt.h
   September 2015
   @author Andrew Daw, Sam Terry, Ben Scott.
   Header file for red black tree rbt.c
 */


#ifndef BST_H_
#define BST_H_

#include <stdbool.h>

typedef struct rbtnode *rbt;


extern rbt rbt_free(rbt b);
extern rbt rbt_insert(rbt b, char *str);
extern rbt rbt_black_root(rbt b);
extern rbt rbt_new();
extern void rbt_preorder(rbt b);
extern bool rbt_is_present(rbt b, char *str);
extern bool rbt_is_empty(rbt);

#endif
