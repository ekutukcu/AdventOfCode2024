#include "util.h"
#include "days.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const int LINE_COUNT = 140;

bool check_direction(int x, int y, int direction[2], char grid[LINE_COUNT][LINE_COUNT])
{
    char xmas[] = "XMAS";
    for(int i=0;i<4;i++)
    {
        if(x<0 || x>=LINE_COUNT || y<0 || y>=LINE_COUNT)
        {
            return false;
        }
        if(grid[x][y]!=xmas[i])
        {
            return false;
        }
        x+=direction[0];
        y+=direction[1];
        
    }
    return true;
}

bool check_x_mas(int x, int y, char grid[LINE_COUNT][LINE_COUNT])
{
    if(x<1 || x>=LINE_COUNT-1 || y<1 || y>=LINE_COUNT-1)
    {
        return false;
    }
    
    bool top_left_bottom_right_correct = ((grid[x-1][y+1]=='M' && grid[x+1][y-1]=='S')
    || (grid[x-1][y+1]=='S' && grid[x+1][y-1]=='M'));

    bool bottom_left_top_right_correct = ((grid[x-1][y-1]=='M' && grid[x+1][y+1]=='S')
    || (grid[x-1][y-1]=='S' && grid[x+1][y+1]=='M'));

    bool centre_correct = grid[x][y]=='A';

    return centre_correct && bottom_left_top_right_correct && top_left_bottom_right_correct;
}

int day04(char *file_name)
{
    char *file_input = read_file(file_name);
    char grid[LINE_COUNT][LINE_COUNT];
    memset( grid, 0, LINE_COUNT*LINE_COUNT*sizeof(char) );

    char *line = strtok(file_input, "\n");
    for (int i = 0; i < LINE_COUNT; i++)
    {
        for (int j = 0; j < LINE_COUNT; j++)
        {
            grid[i][j] = line[j];
        }
        line = strtok(NULL, "\n");
    }

    int directions[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

    int xmas_count=0;
    for (int i = 0; i < LINE_COUNT; i++)
    {
        for (int j = 0; j < LINE_COUNT; j++)
        {
            for(int k=0;k<8;k++)
            {
                if(check_direction(i,j,directions[k], grid))
                {
                    xmas_count++;
                }
            }
        }
    }

    printf("XMAS COUNT: %d\n", xmas_count);

    int x_mas_count = 0;
    for (int i = 0; i < LINE_COUNT; i++)
    {
        for (int j = 0; j < LINE_COUNT; j++)
        {
            if(check_x_mas(i,j,grid))
            {
                x_mas_count++;
            }
        }
    }
    printf("X_MAS COUNT: %d\n", x_mas_count);
}