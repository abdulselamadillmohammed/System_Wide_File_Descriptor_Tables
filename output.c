#include <stdio.h>
#include <stdlib.h>

#include "output.h"
#include "table.h"

/*
 * Prints a simple table showing PID and file descriptor numbers
 * for each entry collected in the FDTable.
 */
void print_per_process_table(FDTable *table) {
    printf("\n");
    printf("         PID     FD\n");
    printf("        ============\n");

    // Iterate through all FD entries and print PID + FD
    for (int i = 0; i < table->size; i++) {
        printf("         %d  %d\n",
               table->entries[i].pid,
               table->entries[i].fd);
    }

    printf("        ============\n");
}

/*
 * Prints the system-wide table showing PID, file descriptor,
 * and the filename associated with the descriptor.
 */
void print_system_wide_table(FDTable *table) {
    printf("\n");
    printf("         PID     FD      Filename\n");
    printf("        ========================================\n");

    // Print each FD entry with its corresponding filename
    for (int i = 0; i < table->size; i++) {
        printf("         %d  %d  %s\n",
               table->entries[i].pid,
               table->entries[i].fd,
               table->entries[i].filename);
    }

    printf("        ========================================\n");
}

/*
 * Prints a vnode-style table mapping file descriptors
 * to their corresponding inode numbers.
 */
void print_vnodes_table(FDTable *table) {
    printf("\n");
    printf("           FD            Inode\n");
    printf("        ========================================\n");

    // Display FD to inode mapping
    for (int i = 0; i < table->size; i++) {
        printf("           %d              %lu\n",
               table->entries[i].fd,
               table->entries[i].inode);
    }

    printf("        ========================================\n");
}

/*
 * Prints a composite table combining PID, FD,
 * filename, and inode information.
 */
void print_composite_table(FDTable *table) {
    printf("\n");
    printf("         PID     FD      Filename                Inode\n");
    printf("        ===============================================\n");

    // Print all collected information for each FD entry
    for (int i = 0; i < table->size; i++) {
        printf("         %d  %d  %s  %lu\n",
               table->entries[i].pid,
               table->entries[i].fd,
               table->entries[i].filename,
               table->entries[i].inode);
    }

    printf("        ===============================================\n");
}

/*
 * Initializes an empty summary table that will track
 * the number of file descriptors per process.
 */
void init_summary_table(SummaryTable *table) {
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

/*
 * Adds a PID to the summary table or increments the
 * existing count if the PID is already present.
 */
void append_or_increment_summary(SummaryTable *table, pid_t pid) {
    PIDSummary *new_entries;
    int new_capacity;

    // Check if this PID already exists in the summary table
    for (int i = 0; i < table->size; i++){
        if (table->entries[i].pid == pid){
            table->entries[i].count++;
            return;
        }
    }

    // Resize the table if capacity is reached
    if (table->size == table->capacity){
        if (table->capacity == 0)
            new_capacity = 10;
        else
            new_capacity = table->capacity * 2;
        
        // Allocate new memory for expanded table
        new_entries = malloc(new_capacity * sizeof(PIDSummary));
        if (new_entries == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        // Copy existing entries into the new array
        for (int i = 0; i < table->size; i++) {
            new_entries[i] = table->entries[i];
        }

        // Replace old storage with the new expanded array
        free(table->entries);
        table->entries = new_entries;
        table->capacity = new_capacity;
    }

    // Add a new PID entry with count initialized to 1
    table->entries[table->size].pid = pid;
    table->entries[table->size].count = 1;
    table->size++;
}

/*
 * Frees memory used by the summary table.
 */
void free_summary_table(SummaryTable *table) {
    free(table->entries);
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

/*
 * Builds the summary table by counting how many file
 * descriptors are associated with each PID.
 */
void build_summary_table(FDTable *fd_table, SummaryTable *summary_table) {
    for (int i = 0; i < fd_table->size; i++) {
        append_or_increment_summary(summary_table, 
                                    fd_table->entries[i].pid);
    }
}

/*
 * Prints the summary table showing each PID and the
 * total number of file descriptors it owns.
 */
void print_summary_table(SummaryTable *summary_table) {
    printf("\n");
    printf("         Summary Table\n");
    printf("         =============\n");

    // Print each PID and its FD count
    for (int i = 0; i < summary_table->size; i++) {
        printf("%d (%d)", summary_table->entries[i].pid,
                         summary_table->entries[i].count);

        if (i < (summary_table->size - 1)) {
            printf(",  ");
        }
    }

    printf("\n");
}

/*
 * Prints processes that exceed a specified file descriptor
 * threshold, indicating potential FD overuse.
 */
void print_threshold_table(SummaryTable *summary_table, int threshold) {
    int found = 0;

    // Ignore invalid thresholds
    if (threshold < 0) {
        return;
    }

    printf("\n");
    printf("## Offending processes:\n");

    // Identify PIDs whose FD count exceeds the threshold
    for (int i = 0; i < summary_table->size; i++) {
        if (summary_table->entries[i].count > threshold) {
            printf("%d (%d)", summary_table->entries[i].pid,
                             summary_table->entries[i].count);
            printf(", ");
            found = 1;
        }
    }

    // If no offending processes were found
    if (!found) {
        printf("None");
    }

    printf("\n");
}