#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "table.h"

// Instead of creating an array to store the state of my 
// arguments then I will update them in the parser;

/*

If no args are passed in:
    cfg->composite = 1


*/


// Compilation step: gcc -Wall -std=c99 process.c -o process
// All args calling

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


 int main(int argc, char** argv){
    // Initalize the flagged argument container

    // For some reason this version is allowed
    // NOTE: add comments clarifying what each predefined arg is 
    // signifying 
    Config cfg = {  0,    
                    0,
                    0,
                    0,
                    0,
                    -1, // Threshold can technically be 0 so set to -1
                    -1};


    // Call to parser
    parser(argc, argv, &cfg);

    /* Default behavior: if no table flag was passed, use composite */
    if (cfg.per_process == 0 &&
        cfg.systemWide == 0 &&
        cfg.Vnodes == 0 &&
        cfg.composite == 0 &&
        cfg.summary == 0) {
        cfg.composite = 1;
    }

    
    printf("Per-process: %d\n", cfg.per_process);
    printf("System-wide: %d\n", cfg.systemWide);
    printf("Vnodes: %d\n", cfg.Vnodes);
    printf("Composite: %d\n", cfg.composite);
    printf("Summary: %d\n", cfg.summary);
    printf("Threshold: %d\n", cfg.threshold);

    printf("Process_id: %d\n", cfg.process_id);

    return 0;
}