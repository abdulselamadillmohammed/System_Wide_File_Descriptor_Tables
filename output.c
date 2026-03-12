#include <stdio.h>

#include "output.h"
#include "table.h"

void print_per_process_table(FDTable *table) {
    printf("\n");
    printf("         PID     FD\n");
    printf("        ============\n");

    for (int i = 0; i < table->size; i++) {
        printf("         %d  %d\n",
               table->entries[i].pid,
               table->entries[i].fd);
    }

    printf("        ============\n");
}

void print_system_wide_table(FDTable *table) {
    printf("\n");
    printf("         PID     FD      Filename\n");
    printf("        ========================================\n");

    for (int i = 0; i < table->size; i++) {
        printf("         %d  %d  %s\n",
               table->entries[i].pid,
               table->entries[i].fd,
               table->entries[i].filename);
    }

    printf("        ========================================\n");
}

void print_vnodes_table(FDTable *table) {
    printf("\n");
    printf("           FD            Inode\n");
    printf("        ========================================\n");

    for (int i = 0; i < table->size; i++) {
        printf("           %d              %lu\n",
               table->entries[i].fd,
               table->entries[i].inode);
    }

    printf("        ========================================\n");
}

void print_composite_table(FDTable *table) {
    printf("\n");
    printf("         PID     FD      Filename                Inode\n");
    printf("        ===============================================\n");

    for (int i = 0; i < table->size; i++) {
        printf("         %d  %d  %s  %lu\n",
               table->entries[i].pid,
               table->entries[i].fd,
               table->entries[i].filename,
               table->entries[i].inode);
    }

    printf("        ===============================================\n");
}

void init_summary_table(SummaryTable *table) {
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

void append_or_increment_summary(SummaryTable *table, pid_t pid) {
    PIDSummary *new_entries;
    int new_capacity;

    for (int i = 0; i < table->size; i++){
        if (table->entries[i].pid == pid){
            table->entries[i].count++;
            return;
        }
    }

    if (table->size == table->capacity){
        if (table->capacity == 0)
            new_capacity = 10;
        else
            new_capacity = table->capacity * 2;
        

        new_entries = malloc(new_capacity * sizeof(PIDSummary));
        if (new_entries == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        for (int i = 0; i < table->size; i++) {
            new_entries[i] = table->entries[i];
        }

        free(table->entries);
        table->entries = new_entries;
        table->capacity = new_capacity;
    }

    table->entries[table->size].pid = pid;
    table->entries[table->size].count = 1;
    table->size++;
}

void free_summary_table(SummaryTable *table) {
    free(table->entries);
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

void build_summary_table(FDTable *fd_table, SummaryTable *summary_table) {
    for (int i = 0; i < fd_table->size; i++) {
        append_or_increment_summary(summary_table, 
                                    fd_table->entries[i].pid);
    }
}

void print_summary_table(SummaryTable *summary_table) {
    printf("\n");
    printf("         Summary Table\n");
    printf("         =============\n");

    for (int i = 0; i < summary_table->size; i++) {
        printf("%d (%d)", summary_table->entries[i].pid,
                         summary_table->entries[i].count);

        if (i < (summary_table->size - 1)) {
            printf(",  ");
        }
    }

    printf("\n");
}

void print_threshold_table(SummaryTable *summary_table, int threshold) {
    int found = 0;

    if (threshold < 0) {
        return;
    }

    printf("\n");
    printf("## Offending processes:\n");

    for (int i = 0; i < summary_table->size; i++) {
        if (summary_table->entries[i].count > threshold) {
            printf("%d (%d)", summary_table->entries[i].pid,
                             summary_table->entries[i].count);
            printf(", ");
            found = 1;
        }
    }

    if (!found) {
        printf("None");
    }

    printf("\n");
}