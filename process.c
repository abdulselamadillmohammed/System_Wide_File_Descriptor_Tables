#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <string.h>
#include <ctype.h>

// Instead of creating an array to store the state of my 
// arguments then I will update them in the parser;


typedef struct{
    int per_process;
    int systemWide;
    int Vnodes;
    int composite;
    int summary;
    int threshold;

    int process_id;
} Config;


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
 void parser(int argc, char** argv, Config* cfg){

    // *(positional_argument) = x; 
    // note to self, see if positional_argument[0] works
    
    for (int i=0; i < (argc-1); i++){
        // i + 1 because we left shift argc to allow for 
        // 0 based indexing
        if (strcmp(argv[i+1], "--per-process") == 0)
            cfg->per_process = 1;

        else if (strcmp(argv[i+1], "--systemWide") ==0 )
            cfg->systemWide = 1;

        else if (strcmp(argv[i+1], "--Vnodes") == 0)
            cfg->Vnodes = 1;

        else if (strcmp(argv[i+1], "--composite") == 0)
            cfg->composite = 1;

        else if (strcmp(argv[i+1], "--summary") == 0)
            cfg->summary = 1;

        else if (strncmp(argv[i+1], "--threshold=", 12) == 0)
            cfg->threshold = atoi(argv[i+1] + 12);
        
        // Check positional argument (all you have to )
        // Note: I'm going to check that the current version i have 
        // is 0 and only will i change
        else if (isdigit(argv[i+1][0])) // If the first digit is a number
            cfg->process_id = atoi(argv[i+1]);
    }
 }
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
                    0, 
                    -1};

    // Call to parser
    parser(argc, argv, &cfg);
/*

typedef struct{
    int per_process;
    int systemWide;
    int Vnodes;
    int composite;
    int summary;
    int threshold;

    int process_id;
} Config;

*/
    printf("Per-process: %d\n", cfg.per_process);
    printf("System-wide: %d\n", cfg.systemWide);
    printf("Vnodes: %d\n", cfg.Vnodes);
    printf("Composite: %d\n", cfg.composite);
    printf("Summary: %d\n", cfg.summary);
    printf("Threshold: %d\n", cfg.threshold);

    printf("Process_id: %d\n", cfg.process_id);

    return 0;
}