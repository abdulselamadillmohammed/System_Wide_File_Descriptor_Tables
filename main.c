// main.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "parser.h"
#include "table.h"
#include "proc.h"
#include "output.h"

int main(int argc, char** argv){

    // Configuration struct storing parsed command-line options
    Config cfg = {0, 0, 0, 0, 0, -1, -1};

    // Tables used to store FD data and aggregated summary information
    FDTable table;
    SummaryTable summary_table;

    // Parse command-line arguments and populate cfg
    parser(argc, argv, &cfg);

    // Default behavior: if no table flag is specified, print the composite table
    if (cfg.per_process == 0 &&
        cfg.systemWide == 0 &&
        cfg.Vnodes == 0 &&
        cfg.composite == 0 &&
        cfg.summary == 0) {
        cfg.composite = 1;
    }

    // Initialize data structures used to store collected FD information
    init_fd_table(&table);
    init_summary_table(&summary_table);

    // If a specific PID was provided, collect FDs only for that process.
    // Otherwise scan all processes belonging to the current user.
    if (cfg.process_id != -1)
        collect_fd_for_pid(cfg.process_id, &table);
    else
        collect_fd_for_all_user_processes(&table);
    
    // Build a summary table counting the number of FDs per PID
    build_summary_table(&table, &summary_table);

    // Print tables depending on which flags were provided

    if (cfg.per_process)
        print_per_process_table(&table);

    if (cfg.systemWide) 
        print_system_wide_table(&table);
    
    if (cfg.Vnodes) 
        print_vnodes_table(&table);
    
    if (cfg.composite) 
        print_composite_table(&table);
        
    if (cfg.summary)
        print_summary_table(&summary_table);

    // Print offending processes if a threshold was specified
    if (cfg.threshold != -1)
        print_threshold_table(&summary_table, cfg.threshold);

    // Free dynamically allocated memory before exiting
    free_fd_table(&table);
    free_summary_table(&summary_table);

    return 0;
}