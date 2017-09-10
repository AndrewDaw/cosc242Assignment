/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"
#include "container.h"

struct htablerec{
    container *keys;
    int capacity;
};
/*for creating hashkeys*/
static unsigned int htable_word_to_int(char *word) {
	unsigned int result = 0;
	while (*word != '\0'){
		result = (*word++ + 31 * result);
	}
	return result;
}
/*creates the hash table, sets it up to hold containers
 *@param size size of hash table
 *@param type type of container ie. FLEX_ARRAY or RED_BLACK_TREE
 */
htable htable_new(int size, container_t type){
    int i;
    htable result = emalloc(sizeof *result);
    result->capacity = size;
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    for(i = 0; i < result->capacity; i++){
        result->keys[i] = container_new(type);
    }
    return result;
}

/*uses the container's append method at given hash_position*/
int htable_insert(htable h, char *str){   
    unsigned int hash_pos = ((htable_word_to_int(str)) % (h->capacity));
    
    container_add(h->keys[hash_pos],str);
    return 0;
}
/*returns true if the string is present*/
bool htable_is_present(htable h, char *str){
    unsigned int hash_pos = htable_word_to_int(str) % h->capacity;
    return container_is_present(h->keys[hash_pos],str);
    
}
/*prints values held at each position of hash table*/
void htable_print(htable h, FILE *strm){
    int i;
    for(i = 0; i < h->capacity; i++){
        if(!container_is_empty(h->keys[i])){
            if(h->keys[i] !=NULL){
                fprintf(strm,"%d", i);
                container_visit(h->keys[i]);
                fprintf(strm,"\n");
            }
        }
    }
}
/*free's all associated memory*/
void htable_free(htable h){
    int i;
    for(i = 0; i > h->capacity; i++){
        container_free(h->keys[i]);
    }
    free(h->keys);
}

