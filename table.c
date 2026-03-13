#include <stdio.h>
#include <stdlib.h>
#include "table.h"

/*
 * Initializes an FDTable structure by setting the
 * dynamic array pointer to NULL and resetting size/capacity.
 */
void init_fd_table(FDTable *table){
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

/*
 * Appends a new FDEntry to the table. If the internal
 * array is full, the capacity is expanded using dynamic
 * memory allocation.
 */
void append_fd_entry(FDTable *table, FDEntry entry)
{
    // Check if we need to grow the dynamic array
    if (table->size == table->capacity)
    {
        int new_capacity;

        // Initial allocation or capacity doubling
        if (table->capacity == 0)
            new_capacity = 10;
        else
            new_capacity = table->capacity * 2;

        // Allocate new memory block
        FDEntry *new_entries = malloc(new_capacity * sizeof(FDEntry));

        if (new_entries == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        // Copy existing entries into new memory
        for (int i = 0; i < table->size; i++)
            new_entries[i] = table->entries[i];

        // Free old memory and update table pointer
        free(table->entries);
        table->entries = new_entries;
        table->capacity = new_capacity;
    }

    // Insert the new entry and increase table size
    table->entries[table->size] = entry;
    table->size++;
}

/*
 * Frees all dynamically allocated memory used by the FDTable
 * and resets the structure to an empty state.
 */
void free_fd_table(FDTable *table){
    free(table->entries);
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}