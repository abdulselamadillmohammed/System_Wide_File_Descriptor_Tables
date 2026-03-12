#ifndef TABLE_H

#define TABLE_H
#define MAX_FILENAME 4096

#include <sys/types.h>

typedef struct {
    pid_t pid;
    int fd;
    char filename[MAX_FILENAME];
    unsigned long inode;
} FDEntry;

typedef struct {
    FDEntry *entries;
    int size;
    int capacity;
} FDTable;

void init_fd_table(FDTable *table);
void append_fd_entry(FDTable *table, FDEntry entry);
void free_fd_table(FDTable *table);
#endif