#include <stdio.h>
#include <stdlib.h>   
#include <string.h>   
#include <ctype.h>   

#include "parser.h"

int is_number_string(char *s){
    int i;
    if (s == NULL || s[0] == '\0'){
        return 0;   
    }

    for (int i = 0; s[i] != '\0'; i++){
        if (!isdigit(s[i])){
            return 0;
        }         
    }
    return 1;

}

void parser(int argc, char** argv, Config* cfg){

    // *(positional_argument) = x; 
    // note to self, see if positional_argument[0] works

    for (int i=1; i <argc; i++){
        // i + 1 because we left shift argc to allow for 
        // 0 based indexing
        if (strcmp(argv[i], "--per-process") == 0)
            cfg->per_process = 1;

        else if (strcmp(argv[i], "--systemWide") ==0 )
            cfg->systemWide = 1;

        else if (strcmp(argv[i], "--Vnodes") == 0)
            cfg->Vnodes = 1;

        else if (strcmp(argv[i], "--composite") == 0)
            cfg->composite = 1;

        else if (strcmp(argv[i], "--summary") == 0)
            cfg->summary = 1;

        else if (strncmp(argv[i], "--threshold=", 12) == 0){  
            char * value = argv[i] + 12;
            if (!is_number_string(value)){
                fprintf(stderr, "Error: invalid threshold value in '%s'\n", argv[i]);
                exit(1);
            }
            cfg->threshold = atoi(value);
        }
        // Check positional argument (all you have to )
        // Note: I'm going to check that the current version i have 
        // is 0 and only will i change
        else if (is_number_string(argv[i])) { // If the first digit is a number
            if (cfg->process_id != -1){
                fprintf(stderr, "Error: only one PID positional argument is allowed.\n");
                exit(1);
            }
            cfg->process_id = atoi(argv[i]);
        }
        else { 
            fprintf(stderr, "Error: invalid argument '%s'\n", argv[i]);
            exit(1);
        }
    }
}
