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

1. Process FD table
- Each process has its own FD table
    - It maps small integer to open file description

eg. Every time you call fork, it clones
the FD table hence why you can pipe with it 

FD 0 → stdin
FD 1 → stdout
FD 2 → stderr
FD 3 → open file A
FD 4 → socket

* Typical ways you can modify FD tables is with:
    - open(), dup(), fork(), close()


2. System wide FD table

- This is kernel-global in that it contains ALL open file descriptors.
- Each entry stores:    
    - The file offset, File status flags (O_APPEND, O_NONBLOCK, etc)
    - Pointer to inode
    - Reference count

* Note: Multiple processes can point to the same system-wide entry.

Example
Process A FD 3  ─┐
                 |--─> System-wide file entry #27
Process B FD 5  ─┘

- If both processes duplicated the FD or inherited via fork, they share the same file offset and same flags


## FD → Disk (Full Chain)