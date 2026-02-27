#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <string.h>

// Parser 
/* The parser will extract the following properties
 * --per-process
 * --systemWide
 * --Vnodes
 * --composite
 * --summary
 * --threshold=X
 * 
 * 
 * DEFAULT BEHAVIOR: if no argument is passed to 
 * the program, you must implement one of the 
 * following approaches. 
 * 
 * 1. the program will display the composite table, 
 * i.e. same effect as having used the --composite 
 * flag
 * 
 * 2. the program will display all the tables, i.e. 
 * same effect as having used all the flagged 
 * arguments  --per-process --systemWide --Vnode 
 * --composite 
 * 
 * Positional argument: 
 *  My role is only to accept on positional argument 
 * which indicates that a particular process id number
 * (PID), if not specified; the program will attempt 
 * to process all the currently running processes for the
 * user executing the program
 * 
 */
 void parser(int argc, char** argv, 
    int* flagged_arguments, int* positional_argument){

    // *(positional_argument) = x; 
    // note to self, see if positional_argument[0] works

 }


int main(int argc, char** argv){
    // Initalize the flagged argument container
    int flagged_arguments[] = {0,0,0,
                               0,0,0};

    int positional_argument = 0;

    return 0;
}