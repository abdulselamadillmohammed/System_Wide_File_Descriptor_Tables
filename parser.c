#include <stdio.h>
#include <stdlib.h>   
#include <string.h>   
#include <ctype.h>   

#include "parser.h"

/*
 * Checks whether a string consists only of numeric characters.
 * Used to validate PID and threshold values.
 */
int is_number_string(char *s){
    // Reject NULL or empty strings
    if (s == NULL || s[0] == '\0'){
        return 0;   
    }

    // Ensure every character is a digit
    for (int i = 0; s[i] != '\0'; i++){
        if (!isdigit(s[i])){
            return 0;
        }         
    }
    return 1;
}

/*
 * Parses command-line arguments and populates the Config struct.
 * Supports flags for different tables and optional PID filtering.
 */
void parser(int argc, char** argv, Config* cfg){

    // Iterate through command-line arguments (skip program name)
    for (int i = 1; i < argc; i++){

        // Enable per-process output
        if (strcmp(argv[i], "--per-process") == 0)
            cfg->per_process = 1;

        // Enable system-wide table output
        else if (strcmp(argv[i], "--systemWide") == 0)
            cfg->systemWide = 1;

        // Enable vnode/inode mapping table
        else if (strcmp(argv[i], "--Vnodes") == 0)
            cfg->Vnodes = 1;

        // Enable composite table output
        else if (strcmp(argv[i], "--composite") == 0)
            cfg->composite = 1;

        // Enable summary table output
        else if (strcmp(argv[i], "--summary") == 0)
            cfg->summary = 1;

        // Parse threshold flag (--threshold=X)
        else if (strncmp(argv[i], "--threshold=", 12) == 0){  
            char *value = argv[i] + 12;

            // Validate threshold value
            if (!is_number_string(value)){
                fprintf(stderr, "Error: invalid threshold value in '%s'\n", argv[i]);
                exit(1);
            }

            cfg->threshold = atoi(value);
        }

        // Handle positional argument representing a PID
        else if (is_number_string(argv[i])) {

            // Ensure only one PID argument is allowed
            if (cfg->process_id != -1){
                fprintf(stderr, "Error: only one PID positional argument is allowed.\n");
                exit(1);
            }

            cfg->process_id = atoi(argv[i]);
        }

        // Any other argument is invalid
        else { 
            fprintf(stderr, "Error: invalid argument '%s'\n", argv[i]);
            exit(1);
        }
    }
}