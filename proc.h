#ifndef PROC_H
#define PROC_H

#include <sys/types.h>
#include "table.h"

void collect_fd_for_pid(pid_t pid, FDTable *Table);
void collect_fd_for_all_user_processes(FDTable *table);

#endif