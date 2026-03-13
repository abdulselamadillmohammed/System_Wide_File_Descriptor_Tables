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
i. Describe first in sentences how did you implement your code.


ii. The modules you created and functions within them.



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

## Test Cases

## Disclaimers


## References
    https://man7.org/linux/man-pages/man5/proc.5.html
    https://tldp.org/LDP/Linux-Filesystem-Hierarchy/html/proc.html 
    https://man7.org/linux/man-pages/man0/dirent.h.0p.html 
    https://man7.org/linux/man-pages/man3/snprintf.3p.html 
    https://man7.org/linux/man-pages/man3/fprintf.3p.html 
    https://man7.org/linux/man-pages/man0/sys_types.h.0p.html 