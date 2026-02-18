#ifndef LIFE_H
#define LIFE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int **create_board(int w, int h);
void free_board(int **b, int h);
void print_board(int **b, int w, int h);
void read_input(int **b, int w, int h);

int count_neighbor(int **b, int h, int w, int y, int x);
int **update_board(int **b, int h, int w);


#endif