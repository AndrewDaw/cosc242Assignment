/**
   The main method for our project.  This main method does the following:
   1) Reads and executes code based on options/arguments read from the command line.
   2) Frees all memory from data structures that were allocated.
   @author Andrew Daw, Benjamin Scott, Samuel Terry.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include "htable.h"
#include "container.h"
#include "mylib.h"
#include <stdbool.h>
#define DEFAULT_HASH_SIZE 3877
#define WSIZE 256


/**
   Prints a help menu if '-h' or any invalid option is
   read from the command line.

*/

void print_usage(){
    fprintf(stderr, "Usage:\nEnter the option '-r' to use a robust chaining\n%s",
            " method like a red-black tree.\n\n");
                
    fprintf(stderr, "Enter the option '-s' followed by an number which\n%s\n%s",
            " will set the size of the hash table, the number",
            " should be greater than zero.\n\n");
                
    fprintf(stderr, "Enter the option '-p' to print out each non-empty\n%s\n%s",
            "  container in your hash table.  An index will be",
            " provided for each container in the hash table.\n\n");
                
    fprintf(stderr, "Enter the option '-i' to find out how long to took to\n%s\n%s",
            " fill and search the hash table, and find the number of",
            " unknown words (words not present in the hash table).\n\n");
}

int main(int argc, char **argv){
    FILE *infile;
    int cmd_file_index;
    int i;
    int unknownWords = 0;
    htable h;
    bool timing, print_table;
    const char *optstring = "rpis:h";
    char option;
    clock_t start, end;
    extern char *optarg;
    container_t type = FLEX_ARRAY;
    int table_size = DEFAULT_HASH_SIZE;
    char word[WSIZE];
    timing = print_table = false;
    cmd_file_index = 1;
   

    
    

    
    /**
       Reads options from the command line.
    */
    
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            /*Sets hashtables chaining method to use a red-black tree*/
            case 'r':
                type = RED_BLACK_TREE;
                break;
                /*Sets table size from command line*/
            case 's':
                table_size = (atoi(optarg));
                break;
            case 'p':
                print_table = true;
            case 'i':
                timing = true;
                break;
            case 'h':
                printf("\n*****HELP-MENU*****\n");
                print_usage();
                return EXIT_SUCCESS;
            default:
                printf("\nInvalid flag\n");
                print_usage();
                return EXIT_SUCCESS;
                break;
        }
    }
    /**
       While there is file input and or more options to be read.
    */
    
    while (NULL == (infile = fopen(argv[cmd_file_index], "r"))) {
        cmd_file_index++;
    }

    /**
       Creates a new hash table.
    */
    h = htable_new(table_size,type);

    
    /**
       If in timing mode start the clock.
    */
        if(timing){
        start = clock();
    }

    /**
       Fills the hash table while more words are read.
    */
while(1 == fscanf(infile, "%s", word)){
        for( i = 0; word[i]; i++){
            word[i] = tolower(word[i]);
        }
        htable_insert(h, word);
    }
 
/**
   If in timing mode clock is stopped and timing information printed.
*/
     if(timing){
        end = clock();
        fprintf(stderr, "Fill time: %f\n", (end - start) / (double)CLOCKS_PER_SEC);
      
    }

     /**
        If in print mode, table is printed and program exited.
     */
     if(print_table){
            htable_print(h, stdout);
            htable_free(h);
            return EXIT_SUCCESS;
        }   
     /**
        While words still read from stdin.
     */
     while(getword(word, sizeof word, stdin) != EOF){    
         /**
            If in timing mode, starts clock before searching hash table.
         */
         if(timing){
             start = clock();
         }
         /**
            Prints word if present in hash table.
         */
         if(! htable_is_present(h, word)){
             printf("%s\n", word);
             unknownWords++;
            
         }
         /**
            If in timing mode, end clock.
            Print search time and the number of unknown words
         */
         if(timing){
             
             end = clock();
             fprintf(stderr, "Search time: %f\nUnknown words: %d\n",
                     (end - start) / (double)CLOCKS_PER_SEC, unknownWords);
         }
         
    }
     
     htable_free(h);
     return EXIT_SUCCESS;
}
         
         
                
