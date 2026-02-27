# System_Wide_File_Descriptor_Tables

![FD Table](assets/FDTable.png)

## The program, will generate:

1. process FD table
2. System-wide FD Table
3. Vnodes FD table, and
4. a composed view of the previous table
5. a table summarizing number of FDs open per user processes

### The program accepts multiple command line arguments

* Flagged arguments
1. --per-process: indicates that only the process FD table will be displayed
2. --systemWide: indicates that only the system-wide FD table will be displayed

### The diffrence between a process FD table and a system-wide FD table