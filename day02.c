
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"

bool is_line_valid_no_removal(int line_numbers[], int num_count)
{
    bool decreasing = line_numbers[0] > line_numbers[1];
    for(int i=0; i<num_count-1; i++)
    {
        int diff = abs(line_numbers[i] - line_numbers[i+1]);
        if(diff < 1 || diff > 3)
        {
            return false;
        }
        else if(decreasing && line_numbers[i] < line_numbers[i+1])
        {
            return false;
        }
        else if(!decreasing && line_numbers[i] > line_numbers[i+1])
        {
            return false;
        }
    }
    return true;
}

bool is_line_valid_with_removal(int line_numbers[], int num_count, int level_to_remove)
{
    int new_line_numbers[num_count-1];
    int written_index = 0;
    for(int i=0; i<num_count; i++)
    {
        if(i == level_to_remove)
        {
            continue;
        }
        new_line_numbers[written_index] = line_numbers[i];
        written_index++;
    }
    return is_line_valid_no_removal(new_line_numbers, num_count-1);
}

bool is_line_valid(int line_numbers[], int num_count)
{
    if(is_line_valid_no_removal(line_numbers, num_count))
    {
        return true;
    }
    for(int i=0;i<num_count;i++)
    {
        if(is_line_valid_with_removal(line_numbers, num_count, i))
        {
            return true;
        }
    }
    return false;
}

const int MAX_NUMBERS_PER_LINE = 10;

int main()
{
    FILE *input_file = fopen("input02.txt", "r");
    if (input_file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    char *file_input = read_file("input02.txt");

    char *line = strtok(file_input, "\n");
    int safeCount1 = 0;
    int safeCount2 = 0;
    int line_numbers[MAX_NUMBERS_PER_LINE]; 
    while (line != NULL)
    {
        char *pEnd;
        int num_count = 0;
        while (*line != '\0')
        {
            int number = strtol(line, &pEnd, 10);
            line_numbers[num_count] = number;
            line = pEnd;
            num_count++;
        }

        if(is_line_valid_no_removal(line_numbers, num_count))
        {
            safeCount1++;
        }
        
        if (is_line_valid(line_numbers, num_count))
        {
            safeCount2++;
        }
        line = strtok(NULL, "\n");
    }
    printf("Safe count part 1: %d\n", safeCount1);
    printf("Safe count part 2: %d\n", safeCount2);
}