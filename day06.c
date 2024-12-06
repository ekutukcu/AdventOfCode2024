#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "days.h"
#include "util.h"
#include "hash_table.h"
#define GRID_SIZE 130

enum direction
{
    up,
    down,
    left,
    right
};

char *direction_to_string(enum direction dir)
{
    switch (dir)
    {
    case up:
        return "UP";
    case right:
        return "RIGHT";
    case down:
        return "DOWN";
    case left:
        return "LEFT";
    }
}

enum direction change_direction(enum direction current_direction)
{
    switch (current_direction)
    {
    case up:
        return right;
    case right:
        return down;
    case down:
        return left;
    case left:
        return up;
    }
    return -1;
}

bool is_within_bounds(int x, int y)
{
    return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE;
}

void print_grid(char grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            putchar(grid[i][j]);
        }

        putchar('\n');
    }
}
typedef struct visited_location
{
    int x;
    int y;
    enum direction dir;
} visited_location;

int encode_position_and_direction(visited_location *loc)
{
    unsigned char x_pos = (unsigned char)loc->x;
    unsigned char y_pos = (unsigned char)loc->y;
    unsigned char dir_byte = (unsigned char)loc->dir;
    int ret = 0;
    ret |= x_pos;
    ret <<= 8;
    ret |= y_pos;
    ret <<= 8;
    ret |= dir_byte;

    return ret;
}

visited_location *create_visited_location(int x, int y, enum direction dir)
{
    visited_location *loc = (visited_location *)malloc(sizeof(visited_location));
    loc->x = x;
    loc->y = y;
    loc->dir = dir;

    return loc;
}
void move_in_direction(enum direction dir, int *x, int *y)
{
    switch (dir)
    {
    case up:
        (*y)--;
        break;
    case down:
        (*y)++;
        break;
    case left:
        (*x)--;
        break;
    case right:
        (*x)++;
        break;
    default:
        break;
    }
}

bool walk_to_end(char grid[GRID_SIZE][GRID_SIZE], bool visited[GRID_SIZE][GRID_SIZE],
    int x, int y)
{
    // init
    enum direction current_direction = up;
    visited[y][x] = true;
    hash_table *visited_locations = hash_table_create(GRID_SIZE * GRID_SIZE);
    visited_location *loc = create_visited_location(x, y, current_direction);
    hash_table_insert(visited_locations, encode_position_and_direction(loc), loc);

    // walk through grid until exit
    while (1)
    {
        int prev_x = x;
        int prev_y = y;
        move_in_direction(current_direction, &x, &y);
        if (!is_within_bounds(x, y))
        {
            break;
        }
        if (grid[y][x] == '#')
        {
            current_direction = change_direction(current_direction);
            // undo move since we couldn't go there
            x = prev_x;
            y = prev_y;
        }
        else
        {
            loc = create_visited_location(x, y, current_direction);
            int encoded_key = encode_position_and_direction(loc);

            hash_table_entry *existing_loc_entry = hash_table_lookup(visited_locations, encoded_key);
            if (existing_loc_entry != NULL)
            {
                visited_location *existing_loc = (visited_location *)existing_loc_entry->value;
                return false;
            }
            hash_table_insert(visited_locations, encoded_key, loc);
            visited[y][x] = true;
        }
    }
    return true;
}

int day06(char *file_name)
{
    char *file_input = read_file(file_name);
    char grid[GRID_SIZE][GRID_SIZE];
    bool visited[GRID_SIZE][GRID_SIZE];
    int x, y;
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            // 11 to skip the newline
            grid[i][j] = file_input[i * (1 + GRID_SIZE) + j];
            if (grid[i][j] == '^')
            {
                x = j;
                y = i;
            }

            visited[i][j] = false;
        }
    }
    print_grid(grid);

    walk_to_end(grid, visited, x,y);

    int step_count = 0;
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (visited[i][j])
            {
                step_count++;
            }
        }
    }
    printf("Moves: %d, Position (%d,%d)\n", step_count, x, y);

    int loop_count = 0;
    for(int i=0;i<GRID_SIZE;i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if(grid[i][j]=='.')
            {
                grid[i][j]='#';
                if(!walk_to_end(grid, visited, x,y))
                {
                    loop_count++;
                }
                grid[i][j]='.';
            }
        }
    }

    printf("Loop count: %d\n", loop_count);
    return 0;
}