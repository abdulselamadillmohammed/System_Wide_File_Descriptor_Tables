#ifndef PARSER_H
#define PARSER_H

typedef struct {
    int per_process;
    int systemWide;
    int Vnodes;
    int composite;
    int summary;
    int threshold;
    int process_id;
} Config;

int is_number_string(char *s);
void parser(int argc, char **argv, Config *cfg);

#endif