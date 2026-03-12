#include <stdio.h>
#include <stdlib.h>
#include "table.h"

void init_fd_table(FDTable *table){
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

void append_fd_entry(FDTable *table, FDEntry entry)
{
    if (table->size == table->capacity)
    {
        int new_capacity;

        if (table->capacity == 0)
            new_capacity = 10;
        else
            new_capacity = table->capacity * 2;

        FDEntry *new_entries = malloc(new_capacity * sizeof(FDEntry));

        if (new_entries == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        for (int i = 0; i < table->size; i++)
            new_entries[i] = table->entries[i];

        free(table->entries);
        table->entries = new_entries;
        table->capacity = new_capacity;
    }

    table->entries[table->size] = entry;
    table->size++;
}
