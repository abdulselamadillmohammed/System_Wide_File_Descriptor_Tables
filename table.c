#include <stdio.h>
#include <stdlib.h>
#include "table.h"

void init_fd_table(FDTable *table){
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

