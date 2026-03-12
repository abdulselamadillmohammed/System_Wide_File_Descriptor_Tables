#ifndef OUTPUT_H
#define OUTPUT_H

#include "table.h"

void print_per_process_table(FDTable *table);
void print_system_wide_table(FDTable *table);
void print_vnodes_table(FDTable *table);
void print_composite_table(FDTable *table);

#endif