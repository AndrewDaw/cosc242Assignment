/**
 Container class.
 Wrapper for a data structure
 Calls methods of underlaying data structure
 @author Andrew, Sam, and Ben
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mylib.h"
#include "container.h"
#include "flexarray.h"
#include "rbt.h"

struct containerrec {
    container_t type;
    void *contents;
};

/**
Container constructor.
@param type. The type of the  data structure contents will hold
@return a container holding the data structure
**/
container container_new(container_t type){
    
    
    if (type == RED_BLACK_TREE) {
        container c = emalloc(sizeof *c);
        c->contents = rbt_new();
        c->type = type;       
        return c;
        
    } else if (type == FLEX_ARRAY) {
        container c = emalloc(sizeof *c);
        c->contents = flexarray_new();
        c->type = type;
        return c;
    }
    return NULL;
}
/**
Calls the insert method of the data structure held by contents.
@param c. The container holding the data structure to insert to
@param *word. Word to be inserted
**/
void container_add(container c, char *word){    
    if (c->type == RED_BLACK_TREE) {
         c->contents = rbt_insert(c->contents, word);
    } else {
        flexarray_append(c->contents, word);
    }
}

/**
Calls the free method of the data structure held by contents.
@param c. The container holding the data structure to be freed from memory
 **/
void container_free(container c){
    if (c->type == RED_BLACK_TREE) {
        c->contents = rbt_free(c->contents);
    } else {
        flexarray_free(c->contents);
    }

}
/**
Calls the is present method of the data structure held by contents.
@param c. The container holding the data structure to be tested
@param *word. A word to be checked if is present in the data structure
@return If the data structure contains the word returns true. Else returns false
**/
bool container_is_present(container c, char *word){
    if (c->type == RED_BLACK_TREE) {
        return (rbt_is_present(c->contents, word));
    } else {
        return flexarray_is_present(c->contents, word);
        
    }
    return false;

}
/**
Calls the is empty method of the data structure held by contents
@param c. The container holding the data structure to be tested
@return true if the data structure is empty. Else false
**/
bool container_is_empty(container c){
    if (c->type == RED_BLACK_TREE) {
        return rbt_is_empty(c->contents);
    }else {
        return flexarray_is_empty(c->contents);
        
    }
    return false;
}




/**
Calls the visit method of the data structure held by contents
@param c. The container to be visited
Note: The visit method of the data structure handles its own printing
**/
void container_visit(container c){
    if (c->type == RED_BLACK_TREE) {
        rbt_preorder(c->contents);
    } else {
        flexarray_visit(c->contents);
    }
}




