#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash_table.h"


int main()
{
    FILE *input_file = fopen("input01.txt", "r");
    if (input_file == NULL)
    {
        perror("Error: could not open file.");
        return 1;
    }

    int size = 16;
    int *list1 = (int *)calloc(size, sizeof(int));
    int *list2 = (int *)calloc(size, sizeof(int));

    int read_count = 0;
    while (1)
    {
        int number1, number2;
        int matched_count = fscanf(input_file, "%d   %d\n", &number1, &number2);
        if (matched_count != 2)
        {
            printf("Could not read numbers from file, matched %d.", matched_count);
        }
        else
        {
            list1[read_count] = number1;
            list2[read_count] = number2;
            read_count++;

            // double the size of the arrays
            if (read_count == size)
            {
                printf("Re-allocating array from %d to %d\n", size, size * 2);
                size *= 2;
                list1 = (int *)realloc(list1, sizeof(int)*size);
                list2 = (int *)realloc(list2, sizeof(int)*size);
            }
        }
        if (feof(input_file))
        {
            break;
        }
    }

    printf("Read %d lines.\n", read_count);
    qsort(list1, read_count, sizeof(int), compare_ints);
    qsort(list2, read_count, sizeof(int), compare_ints);
    int total = 0;
    for (int i = 0; i < read_count; i++)
    {
        int diff = abs(list1[i] - list2[i]);
        total += diff;
        printf("%d %d ---> %d, total=%d\n", list1[i], list2[i], diff, total);
    }

    fclose(input_file);
    printf("Total difference: %d\n", total);

    struct hash_table *list2_dict = hash_table_create(read_count);
    for (int i = 0; i < read_count; i++)
    {
        struct hash_table_entry *found = hash_table_lookup(list2_dict, list2[i]);
        if (found == NULL)
        {
            hash_table_insert(list2_dict, list2[i], 1);
        }
        else
        {
            hash_table_insert(list2_dict, list2[i], found->value + 1);
        }
    }

    int similarity_score = 0;
    for (int i = 0; i < read_count; i++)
    {
        int value = list1[i];
        struct hash_table_entry *found = hash_table_lookup(list2_dict, value);
        if (found != NULL)
        {
            similarity_score += value * found->value;
        }
    }
    printf("Similarity score: %d", similarity_score);
}
