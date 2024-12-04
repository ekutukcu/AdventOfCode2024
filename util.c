#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file(const char *file_name)
{
    FILE *input_file = fopen(file_name, "r");
    if (input_file == NULL)
    {
        printf("Could not open file\n");
        exit(1);
    }
    char *buffer = 0;
    long length;
    fseek(input_file, 0, SEEK_END);
    length = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer)
    {
        fread(buffer, 1, length, input_file);
    }
    fclose(input_file);

    return buffer;
}

int compare_ints(const void *a, const void *b)
{
    int value_a = *(int *)a;
    int value_b = *(int *)b;
    return value_a - value_b;
}

int count_lines(const char * text)
{
    int total_length = strlen(text);
    int line_count = 0;
    for(int i=0;i<total_length;i++)
    {
        if(text[i]=='\n')
        {
            line_count++;
        }
    }
    return line_count;
}