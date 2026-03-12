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


#endif