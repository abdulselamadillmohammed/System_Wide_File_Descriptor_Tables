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
    
    for (int i=0; i < (argc-1); i++){
        // i + 1 because we left shift argc to allow for 
        // 0 based indexing
        if (strcmp(argv[i+1], "--per-process") == 0)
            flagged_arguments[0] = 1;

        else if (strcmp(argv[i+1], "--systemWide") ==0 )
            flagged_arguments[1] = 1;

        else if (strcmp(argv[i+1], "--Vnodes") == 0)
            flagged_arguments[2] = 1;

        else if (strcmp(argv[i+1], "--composite") == 0)
            flagged_arguments[3] = 1;

        else if (strcmp(argv[i+1], "--summary") == 0)
            flagged_arguments[4] = 1;

        else if (strncmp(argv[i+1], "--threshold", 11) == 0)
            flagged_arguments[5] = atoi(argv[i+1] + 11);
        
        // Check positional argument (all you have to )
        // Note: I'm going to check that the current version i have 
        // is 0 and only will i change
        else if (isdigit(argv[i+1][0])) // If the first digit is a number
            *(positional_argument) = atoi(argv[i+1]);
    }
 }


int main(int argc, char** argv){
    // Initalize the flagged argument container
    int flagged_arguments[] = {0,0,0,
                               0,0,0};

    int positional_argument = -1;

    // Call to parser
    parser(argc, argv, flagged_arguments, &positional_argument);

    for (int i = 0; i < 6; i++)
        printf("Postional argument: %d = %d \n", i, flagged_arguments[i]);

    printf("%d", positional_argument);
    return 0;
}