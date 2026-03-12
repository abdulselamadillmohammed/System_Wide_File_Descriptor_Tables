#ifndef OUTPUT_H
#define OUTPUT_H

#include "table.h"

typedef struct {
    pid_t pid;
    int count;
} PIDSummary;

typedef struct {
    PIDSummary *entries;
    int size;
    int capacity;
} SummaryTable;

void print_per_process_table(FDTable *table);
void print_system_wide_table(FDTable *table);
void print_vnodes_table(FDTable *table);
void print_composite_table(FDTable *table);

void init_summary_table(SummaryTable *table);
void append_or_increment_summary(SummaryTable *table, pid_t pid);
void free_summary_table(SummaryTable *table);
void build_summary_table(FDTable *fd_table, SummaryTable *summary_table);

void print_summary_table(SummaryTable *summary_table);
void print_threshold_table(SummaryTable *summary_table, int threshold);

#endif