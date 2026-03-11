#include <stdio.h>

int main(int argc, char** argv){

    FILE *f = fopen("/proc/self/status", "r");

    if (!f){
        perror("fopen");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f))
    {
        printf("%s\n", buffer);
    }
    

    fclose(f);
    return 0;
}