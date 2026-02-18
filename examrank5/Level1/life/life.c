#include "life.h"

//1. creat board
int **create_board(int w, int h)
{
    int **b = calloc(h, sizeof(int *));
    for(int i = 0; i < h; i++)
    b[i]=calloc(w, sizeof(int));
    return b;
}

//2.free board
void free_board(int **b, int h)
{
    for(int i = 0; i < h; i++)
        free(b[i]);
    if(b)
        free(b);
}

//3.print board
void print_board(int **b, int w, int h)
{
    for(int i = 0; i < h; i++, putchar('\n'))
    for(int j=0; j < w; j++)
    putchar(b[i][j] ? '0' : ' ');
}

//4. read_input
void read_input(int **b, int w, int h)
{
    int x = 0, y = 0, draw = 0;
    char c;

    while(read(0, &c, 1) > 0)
    {
        if(c == 'x') draw = !draw;
        else if(c == 'w' && y>0) y--;
        else if(c =='a' && x > 0)x--;
        else if (c =='s' && y< h-1)y++;
        else if(c == 'd' && x < w-1)x++;
        if(draw) b[y][x]=1;
    }
}

//5. count neighbor
int count_neighbor(int **b, int h, int w, int y, int x)
{
    int c = 0;

    for(int i = -1; i<= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if((i || j) && y + i >= 0 && y + i < h && x+j >=0 && x+j < w)
                c+= b[y + i][x + j];
        }
    }
    return c;
}

//6. update board
int **update_board(int **b, int h, int w)
{
    int **n= create_board(w, h);
    for(int y = 0; y < h; y++)
    for(int x = 0; x < w; x++)
    {
        int c = count_neighbor(b,h, w, y,x);
        if(b[y][x])
            n[y][x]= (c == 2 || c == 3);
        else
            n[y][x] = (c == 3);
    }
    free_board(b, h);
    return n;
}

//7.main
int main(int ac, char **av)
{
    if(ac != 4)
        return 1;
    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int it = atoi(av[3]);

    if(w <= 0 || h <= 0 || it < 0) return 1;

    int **board = create_board(w, h);
    if(!board) return 1;

    read_input(board, w, h);
    for(int i = 0; i < it; i++)
      board = update_board(board, w, h);
    
    print_board(board, w, h);
    free_board(board, h);

    return 0;
}