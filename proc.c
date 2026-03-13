// proc.c
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

/*
 * Collects all file descriptors for a specific PID by scanning
 * the /proc/<pid>/fd directory and storing entries in FDTable.
 */
void collect_fd_for_pid(pid_t pid, FDTable *table){
    struct dirent *entry;
    char fd_dir_path[1024];

    // Construct the path to the process's fd directory
    snprintf(fd_dir_path, sizeof(fd_dir_path), "/proc/%d/fd", pid);

    DIR *fd_dir = opendir(fd_dir_path);
    if (!fd_dir){
        return; // Cannot access process directory
    }

    // Iterate through all entries in /proc/<pid>/fd
    while ((entry = readdir(fd_dir)) != NULL) {
        FDEntry fd_entry;
        char link_path[1024];
        char target_path[MAX_FILENAME]; 
        struct stat st;
        ssize_t len;

        // Skip entries that are not numeric file descriptors
        if (!is_number_string(entry->d_name)) {
            continue;
        }

        // Store PID and FD number
        fd_entry.pid = pid;
        fd_entry.fd = atoi(entry->d_name);
        
        // Build path to the symbolic link representing the FD
        snprintf(link_path, sizeof(link_path), "/proc/%d/fd/%s", pid, entry->d_name);

        // Resolve the symbolic link to get the filename
        len = readlink(link_path, target_path, sizeof(target_path) - 1);
        if (len == -1) 
            strcpy(fd_entry.filename, "unreadable");
        else {
            target_path[len] = '\0';
            strcpy(fd_entry.filename, target_path);
        }

        // Retrieve inode information for the file descriptor
        if (stat(link_path, &st) == -1) 
            fd_entry.inode = 0;
        else 
            fd_entry.inode = st.st_ino;
        
        // Add the entry to the FD table
        append_fd_entry(table, fd_entry);

    }
    
    // Close the directory once scanning is complete
    closedir(fd_dir);
}

/*
 * Scans the /proc directory to find all processes owned by
 * the current user and collects their file descriptors.
 */
void collect_fd_for_all_user_processes(FDTable *table){
    DIR *proc_dir;
    struct dirent *entry;
    uid_t current_uid;

    // Get UID of the current user
    current_uid = getuid();

    proc_dir = opendir("/proc");
    if (proc_dir == NULL){
        return;
    }

    // Iterate through all entries in /proc
    while ((entry = readdir(proc_dir)) != NULL) {
        char proc_path[1024];
        struct stat st;
        pid_t pid;
        
        // Only consider numeric directory names (process IDs)
        if (!is_number_string(entry->d_name)) {
            continue;
        }

        pid = atoi(entry->d_name);
        sprintf(proc_path, "/proc/%d", pid);

        // Get metadata about the process directory
        if (stat(proc_path, &st) == -1)
            continue;
        
        // Only collect FDs for processes owned by the current user
        if (st.st_uid == current_uid) 
            collect_fd_for_pid(pid, table);
    }

    // Close /proc directory
    closedir(proc_dir);
}