
#include <stdio.h>
#include <stdlib.h>

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