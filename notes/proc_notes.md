# proc(5) — Linux manual page

* Notes from manual 7

## proc contains process information, system information and sysctl pseudo filesystem

### Description 

The proc filesystem is a pseudo-filesystem that provides an interface to datastructures maintained by the kernel. 

It is commonly mounred at /proc??:
    - The kernel exposes process and system information through a virtual filesystem, and that filesystem is usually attached (“mounted”) at the directory
        /proc

* Files don’t exist on disk.
* They’re generated dynamically by the kernel.
* Reading them queries kernel data structures.

Note: it is typically mounted automatically, however you can manually
do it via:  

* mount -t proc proc /proc

Most of the files in the proc filesystem are read-only however some files are writable as well which technically allows you to change kernel variables 


---
Within the /proc virtual filesystem, there are the following general groups of files and subdirectories

1. /proc/pid subdirectories 
    - Each one of these subdirectories contains files and subdirectories exposing information about the process within the corresponding process ID.

    - Within each of the /proc/pid directories, a task subdirectory contains subdirectories of the dorm task/tid, which contain corresponding informaiton about each pf the threads in the processes where tid is the kernel thread ID of the the thread. 

    - The /proc/pid subdirectories are visible when iterating through /proc with getdents(2) and as such as visible when one uses ls(1) in order to view the contents of /proc

2.        /proc/[a-z]*  
    Various other files and subdirectories under /proc expose
    system-wide information.

