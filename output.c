#include <stdio.h>
#include "output.h"
#include "table.h"

void print_per_process_table(FDTable *table) {
    int i;

    printf("\n");
    printf("         PID     FD\n");
    printf("        ============\n");

    for (i = 0; i < table->size; i++) {
        printf("         %d  %d\n",
               table->entries[i].pid,
               table->entries[i].fd);
    }

    printf("        ============\n");
}

void print_system_wide_table(FDTable *table) {
    int i;

    printf("\n");
    printf("         PID     FD      Filename\n");
    printf("        ========================================\n");

    for (i = 0; i < table->size; i++) {
        printf("         %d  %d  %s\n",
               table->entries[i].pid,
               table->entries[i].fd,
               table->entries[i].filename);
    }

    printf("        ========================================\n");
}

void print_vnodes_table(FDTable *table) {
    int i;

    printf("\n");
    printf("           FD            Inode\n");
    printf("        ========================================\n");

    for (i = 0; i < table->size; i++) {
        printf("           %d              %lu\n",
               table->entries[i].fd,
               table->entries[i].inode);
    }

    printf("        ========================================\n");
}

void print_composite_table(FDTable *table) {
    int i;

    printf("\n");
    printf("         PID     FD      Filename                Inode\n");
    printf("        ===============================================\n");

    for (i = 0; i < table->size; i++) {
        printf("         %d  %d  %s  %lu\n",
               table->entries[i].pid,
               table->entries[i].fd,
               table->entries[i].filename,
               table->entries[i].inode);
    }

    printf("        ===============================================\n");
}