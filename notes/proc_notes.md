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

