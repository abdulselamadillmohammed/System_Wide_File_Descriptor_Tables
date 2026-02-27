// process_creator.c

// This file contains basic template of how to 
// create processes

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char** argv){
    pid_t result;
    int i;

    i = 5;
    printf("%d\n", i);

    result = fork(); // result gets the pid of child if the process
    // is the parent, if it is the child, it will be set to 0
    // if negative, fork failed
    if (result < 0){
        perror("Result failed");
        exit(1);
    }

    return 0;
}