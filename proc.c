#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "proc.h"
#include "table.h"
#include "parser.h"

void collect_fd_for_pid(pid_t pid, FDTable *table){
    struct dirent *entry;
    char fd_dir_path[1024];

    snprintf(fd_dir_path, sizeof(fd_dir_path), "/proc/%d/fd", pid);

    DIR *fd_dir = opendir(fd_dir_path);
    if (!fd_dir){
        return;
    }

    while ((entry = readdir(fd_dir)) != NULL) {
        FDEntry fd_entry;
        char link_path[1024];
        char target_path[MAX_FILENAME]; 
        struct stat st;
        ssize_t len;

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        if (!is_number_string(entry->d_name)) {
            continue;
        }

        fd_entry.pid = pid;
        fd_entry.fd = atoi(entry->d_name);
        
        snprintf(link_path, sizeof(link_path), "/proc/%d/fd/%s", pid, entry->d_name);

        len = readlink(link_path, target_path, sizeof(target_path) - 1);
        if (len == -1) 
            strcpy(fd_entry.filename, "unreadable");
        else {
            target_path[len] = '\0';
            strcpy(fd_entry.filename, target_path);
        }

        if (stat(link_path, &st) == -1) 
            fd_entry.inode = 0;
        else 
            fd_entry.inode = st.st_ino;
        
        append_fd_entry(table, fd_entry);

    }
    
    closedir(fd_dir);
}

