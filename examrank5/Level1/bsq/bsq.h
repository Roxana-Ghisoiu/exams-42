#ifndef BSQ_H
#define BSQ_H


#include <stdlib.h>
#include <stdio.h>

typedef struct s_map
{
    int rows, cols;
    char empty, obst, full;
    char **g;
}    t_map;


int min3(int a, int b, int c);
void free_map(t_map *m);
int parse_header(FILE *fp, t_map *m);
int read_grid(FILE *fp, t_map *m);
int read_map(FILE *fp, t_map *m);
void solve_bsq(t_map *m);

#endif