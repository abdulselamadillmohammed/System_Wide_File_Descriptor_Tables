#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "parser.h"
#include "table.h"
#include "proc.h"


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
    Config cfg = {0, 0, 0, 0, 0, -1, -1};
    FDTable table;

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

    init_fd_table(&table);

    if (cfg.process_id != -1) {
        collect_fd_for_pid(cfg.process_id, &table);
    } else {
        collect_fd_for_all_user_processes(&table);
    }

    printf("Stored entries: %d\n", table.size);

    for (int i = 0; i < table.size; i++) {
        printf("PID: %d  FD: %d  File: %s  Inode: %lu\n",
               table.entries[i].pid,
               table.entries[i].fd,
               table.entries[i].filename,
               table.entries[i].inode);
    }

    free_fd_table(&table);
    return 0;
}