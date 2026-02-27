# The purpose of this tool is to act as a display for the tables which will be used by the OS to keep track of open files, assignation of File Descriptors (FD) and processes. 

## General idea
- The basic idea is that the OS relies on a table which contains file descriptors which have a property of inode which then gets mapped to a palce in hard disk called datablocks

- The basic 3 which are implemented as STDIN STDOUT and STDERR mapped to FDs (0,1,2)

- First define them in the table then allow process allocators to point processes to FDs 

----

The idea presented is to explore /proc

Under /proc we can find a lot of information and resources description from the actual system.

