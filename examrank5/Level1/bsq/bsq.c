#include "bsq.h"

//1 utility func
int min3(int a, int b, int c)
{
    if(a <= b && a <= c) return a;
    if(b <= a && b <= c) return b;
    return c;
}

//2. free map
void free_map(t_map *m)
{
    for(int i= 0; i < m->rows; i++)
        free(m->g[i]);
    free(m->g);
}

//3.parse header
int parse_header(FILE *fp, t_map *m)
{
    char *line=NULL;
    size_t cap = 0;
    int len = 0;

    if(getline(&line, &cap, fp) < 0) return 0;
    while(line[len] && line[len] != '\n')len++;

    m->empty= line[len-3];
    m->obst = line[len-2];
    m->full = line[len-1];
    m->rows = 0;

    for(int i = 0; i < len-3; i++)
        m->rows = m->rows * 10 + (line[i] - '0');
    free(line);
    return 1;
}

//4. read grid
int read_grid(FILE *fp, t_map *m)
{
    char *line=NULL;
    size_t cap = 0;

    m->cols=0;
    m->g= calloc(m->rows, sizeof(char*));

    if(!m->g)
        return 0;

    for(int i= 0; i < m->rows; i++)
    {
        if(getline(&line, &cap, fp) < 0) return 0;
        if(i == 0)
        while(line[m->cols] && line[m->cols] != '\n')
            m->cols++;

        m->g[i] = line;
        line = NULL; cap = 0;
    }
    return 1;
}

//5. read header and grid
int read_map(FILE *fp, t_map *m)
{
    if(!parse_header(fp, m)) return 0;
    if(!read_grid(fp, m)) return 0;
    return 1;
}

//6. solve bsq
void solve_bsq(t_map *m)
{
    int *dp = calloc(m->cols, sizeof(int));
    int best = 0, bi = 0, bj = 0;

    for (int i = 0; i < m->rows; i++)
    {
        int prev = 0, left = 0;
        for (int j = 0; j < m->cols; j++)
        {
            int up = dp[j];

            if (m->g[i][j] == m->obst)
                dp[j] = 0;
            else if (i == 0 || j == 0)
                dp[j] = 1;
            else
                dp[j] = 1 + min3(up, left, prev);

            if (dp[j] > best) { best = dp[j]; bi = i; bj = j; }
            prev = up;
            left = dp[j];
        }
    }
    for (int i = bi - best + 1; i <= bi; i++)
        for (int j = bj - best + 1; j <= bj; j++)
            m->g[i][j] = m->full;

    free(dp);
}

//7.main
int main (int ac, char **av)
{
    FILE *fp=(ac < 2) ? stdin : fopen(av[1], "r");
    t_map m;

    if(!fp || !read_map(fp, &m))
        return fprintf(stderr, "map error\n");

    solve_bsq(&m);

     for(int i= 0; i < m.rows; i++)
        fputs(m.g[i], stdout);

    free_map(&m);
    if(fp != stdin) fclose(fp);
    return 0;
}
