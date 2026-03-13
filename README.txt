Title -- Recreating the System-Wide FD Tables— CSCB09 Assignment 2


## Metadata
    * Author: Abdulselam Adill Mohammed
    * Date: Thursday, March 12, 2026
    * Release/Version: 1.0

## Introduction/Rationale

In Linux, every running process may have several open file 
descriptors which represent files, pipes or other resources. 
The kernel exposes this information via the virtual file system:
/proc. This project is a utility tool which allows one to inspect 
the  file descriptor tables which are used by the operating 
system to manage said open files. 

## Description of how you solve/approach the problem

The main idea behind the implementation in this project is to 
first collect file decriptor information once and then use 
that to generate multiple views of the data. 

The program first parses command line arguments to answer 
fundamental questions such as which tables should be printed, 
and if to generate to a specific pid and whether a threshold filter
should be applied.  

Following that, the program creates a dyanmic table which stores
one record for each open file descriptor that was found. Each 
record contains the process id, file descriptor number, filename
or symbolic link target and inode number. 

After that, /proc is scanned and the program generates the requested
tables using the stored data where each output prints different 
fields from the same underlying data structure. 

Lastly, memory that was allocated for the dynamic table is freed. 


## Implementation

The project is implemented in a modular manner where different
source files have different repsonsibilites. 
Modules: 
    main.c
    parser.c
    proc.c
    table.c
    output.c

main.c:
    This module acts as the entry of the program and controls the 
    execution flow. It intializes the main data structures and 
    calls upon other modules for necessary functionality before 
    finally freeing allocated memory. 

parser.c
    This module is reponsible for parsing the command line arguments
    via the parser() function and updates the config structure. 

    The parser is reponsible for extracting:
        --per-process
        --systemWide
        --Vnodes
        --composite
        --summary
        --threshold=X
        pid provided as a positional argument

    This module also implements is_number_string() which is used to
    ensure what are supposed to be numerical inputs are infact 
    numerical thereby avoiding type conversion issues. 

table.c
    This module implements the dyanmic storage structure which is 
    used to store the file descriptor entries. 

    functions:  
        init_fd_table():

        Initializes the table structure by setting its size and 
        capacity to zero.

        append_fd_entry():

        Adds a new file descriptor record to the table. If the 
        table is full, memory is reallocated to increase capacity.

        free_fd_table():

        Releases memory allocated for the table.

proc.c:
    This module is repsonsible for interacting with the /proc 
    filesystem in order to get information about open file 
    descriptors. 

    Functions:
        collect_fd_for_pid(): this reads /proc/pid/fd and gets 
        all the file descriptors that belong to said pid. It 
        functions by opening the proc/pid/fd directory, iterating 
        through all the entires, reading the symbolic link 
        associated with each file descriptor and obtaining the 
        inode informaiton using stat() and then stores the results
        in the FD table. 

        collect_fd_for_all_user_processes(): scans the /proc directory 
        to find all processes belonging to the current user and for 
        each process it verifies that the directory name is numeric, 
        checks that the processes belongs to the current use and then
        calls collect_fd_for_pid() to gather file descriptor information

output.c:
    This module is reponsible for formatting and printing the 
    desired output tables

    Functions:  
        print_per_process_table()
        print_system_wide_table()
        print_vnodes_table()
        print_composite_table()
        print_summary_table()
        print_threshold_table()

### Include a pseudo-code of your code.

parse command line arguments

intialize FD table 

if pid was passed in:
    collect file descriptors for that pid
else
    collect file descriptors for all user processes

build summary table using fd entries 

if per-process flag
    print per-process table

if systemWide flag
    print system-wide table

if Vnodes flag
    print vnode table

if composite flag
    print composite table

if summary flag
    print summary table

if threshold flag
    print processes exceeding threshold

free allocated memory

### Include a flow chart or diagram of your program and corresponding functions' calls.
    * This is included as an image in the submission called: Flowchart.pdf

## Instructions in how to compile your code
make // this process an executable: showFDtables
     // use make help for all options

./showFDtables [args]

## Expected Results
The program should correctly display file descriptor information 
for running processes.

## Test Cases

1. Default behaviour
./showFDtables

2. Specific pid
./showFDtables pid

3. Invalid argument
./showFDtables --threshold=abc

4. Multiple flags
./showFDtables --summary --composite

## Disclaimers

The default behaviour i chose is no argument is passed to the program 
is to display the composite table.


## References
    https://man7.org/linux/man-pages/man5/proc.5.html
    https://tldp.org/LDP/Linux-Filesystem-Hierarchy/html/proc.html 
    https://man7.org/linux/man-pages/man0/dirent.h.0p.html 
    https://man7.org/linux/man-pages/man2/lstat.2.html
    https://man7.org/linux/man-pages/man3/snprintf.3p.html 
    https://man7.org/linux/man-pages/man3/fprintf.3p.html 
    https://man7.org/linux/man-pages/man0/sys_types.h.0p.html 