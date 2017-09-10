/**
   rbt.c
   September 2015
   @author Andrew Daw, Sam Terry, Ben Scott
   C file for red black tree rbt.h
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rbt.h"
#include "mylib.h"
#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))
typedef enum{ RED, BLACK } rbt_colour;



struct rbtnode {
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
};
/**
   Ensures that the root is black to abide by rbt rules.
   @param b the root of the rbt to make black.
   @return b the bt with a black root. 
 */
rbt rbt_black_root(rbt b){
    if(IS_RED(b)){
        b->colour = BLACK;
    }
    return b;
}

/**
    Takes a rbt as input and rotates it right around the root.
    @param b the bst to be rotated.
    @return b the bst after being rotated.

 */
static rbt right_rotate(rbt b){

    rbt temp = b;
    b = b->left;
    temp->left = b->right;
    b->right = temp;

    return b;
}
/**
   Takes rbt as input and checks if its NULL.
   @param b the rbt to be checked
   @return true if empty
 */
bool rbt_is_empty(rbt b){
    return(b==NULL);
}
/**
    Takes a rbt as input and rotates left around the root.
    @param b the bst to be rotated.
    @return b the bst after being rotated.
 */
static rbt left_rotate(rbt b){

    rbt temp = b;
    b = b->right;
    temp->right = b->left;
    b->left = temp;

    return b;
}

/**
   Takes rbt as input and checks for any violations and fixes them as found.
   @param b the rbt to be checked and fixed.
   @return b the rbt after being fixed 
 */
static rbt rbt_fix(rbt b){

    /* If left child and left child's left child consecutive reds. */ 
    if(IS_RED(b->left) && (IS_RED(b->left->left))){
        if(IS_RED(b->right)){
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        }else{
            b = right_rotate(b);
            b->colour = BLACK;
            b->right->colour = RED;
        }
    }

    /* If left child and left child's right child consecutive reds. */
    if(IS_RED(b->left) && IS_RED(b->left->right)){
        
        if(IS_RED(b->right)){
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        }else{
            b->left = left_rotate(b->left);
            b = right_rotate(b);
            b->colour = BLACK;
            b->right->colour = RED;
        }
    }

    /* If right child and right child's left child consecutive reds. */
    if(IS_RED(b->right) && IS_RED(b->right->left)){
        if(IS_RED(b->left)){
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        }else{
            b->right = right_rotate(b->right);
            b = left_rotate(b);
            b->colour = BLACK;
            b->left->colour = RED;
        }
    }
    /* If right child and right child's right child consecutive reds. */
    if(IS_RED(b->right) && IS_RED(b->right->right)){
        if(IS_RED(b->left)){
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        }else{
            b = left_rotate(b);
            b->colour = BLACK;
            b->left->colour = RED;
        }      
    }

    
    if(b->left != NULL){
        b->left = rbt_fix(b->left);
    }
    if(b->right != NULL){
        b->right = rbt_fix(b->right);
    }
    return b;
}


/** bst constructor, creates a rbt with a NULL value.
    @return the NULL rbt created.
 */
rbt rbt_new(){
    
    rbt b = NULL;
    return b;
}
/**
    Frees memory allocated for given rbt.
    @param b rbt to be freed.
    @return b rbt after being feed. 
 */
rbt rbt_free(rbt b){
    if(b->left != NULL){
        b->left = rbt_free(b->left);
    }
    if(b->right != NULL){
        b->right = rbt_free(b->right);
    }
    free(b);
    b = NULL;
    return b;
}

/**
    Inserts value given into rbt.
    @param b The rbt the string is to be inserted into.
    @param str The string to be inserted into the rbt.
    @return b The rbt after the value has been added to it. 
 */
rbt rbt_insert(rbt b, char *str){

    /* if leaf node, then insert there. */
    if(b == NULL){
        b = emalloc(sizeof(struct rbtnode));
        b->key = str;
        b->colour = RED;
        b->left = rbt_new();
        b->right = rbt_new();
        return b;
    }
    
    /* if larger than key, insert to right. If less than, left */
    if(strcmp(str, b->key)>0){
        b->right = rbt_insert(b->right, str);
        b = rbt_fix(b);
        return b;       
    }else{
        b->left = rbt_insert(b->left, str);
        b = rbt_fix(b);
        return b;
    }
    
}

/**
    Searches for a value within the given bst.
    @param b the bst to search in.
    @param str the string to be searched.
    @return int, 1 if item found, 0 if not.
*/
bool rbt_is_present(rbt b, char *str){
    if(b == NULL){
        return false;
    }
        if(strcmp(b->key, str)==0){

            return true;
        }

        if(strcmp(str, b->key)>0){
            if(b->right == NULL){
                return false;
            }else{
                return rbt_is_present(b->right, str);
            }
        }else{
            if(b->left == NULL){
                return false;
            }else{
                return rbt_is_present(b->left, str);
            }
        }
    
    return false;
}

/**
   Prints out the rbt given in preorder traversal.
   @param b rbt to be traversed and printed.
 */
void rbt_preorder(rbt b){

    if( b == NULL){
        return;
    }
    if(IS_RED(b)){
        printf(" %s",b->key);
    }
    if(IS_BLACK(b)){
        printf(" %s",b->key);
    }
    
    rbt_preorder(b->left);
    rbt_preorder(b->right);
}

  



