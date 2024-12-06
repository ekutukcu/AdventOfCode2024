#include "days.h"
#include "util.h"
#include "hash_table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *find(char *input, char to_find, int line_len)
{
    for (int i = 0; i < line_len; i++)
    {
        if (*(input + i) == to_find)
        {
            return input + i;
        }
    }
    return NULL;
}

int parse_numbers_into_array(char *input_line, int numbers[100])
{
    int count = 0;
    int index = 0;
    int line_len = strlen(input_line);
    while (index < line_len)
    {
        char *remaining_line = input_line + index;
        int parsed_num = atoi(remaining_line);
        numbers[count++] = parsed_num;

        while (index < line_len && input_line[index] != ',')
        {
            index++;
        }
        index++;
    }
    return count;
}

#define MAX_RULE_COUNT 1000

typedef struct rule_set
{
    int count;
    int rules[MAX_RULE_COUNT];
} rule_set;

int sort_line_and_find_middle(int numbers[100], int numbers_count, hash_table * rule_set_hash_table)
{
    int sorted_numbers[100];
    int sorted_numbers_index = 0;
    for(int i=numbers_count-1;i>=0;i++)
    {
        for(int j=numbers_count-1;j>=0;j++)
        {
            int number = numbers[j];
            hash_table_entry* found_rules_entry = hash_table_lookup(rule_set_hash_table, number);
            if(found_rules_entry==NULL)
            {
                sorted_numbers[i]=number;

            }
            else
            {
                rule_set * rules = found_rules_entry->value;
                for(int k=0;k<rules->count;k++)
                {
                    int before = rules->rules[k];
                }
            }

        }

    }
    return 0;
} 

int day05(char *file_name)
{
    char *rule_lines = read_file(file_name);
    char *test_lines = strstr(rule_lines, "\n\n");
    *test_lines = '\0';
    test_lines += 2;

    int rule_count = count_lines(rule_lines);
    int test_line_count = count_lines(test_lines);
    printf("Rule Count: %d\n", rule_count);
    printf("Input Count: %d\n", test_line_count);

    hash_table *rule_set_hash_table = hash_table_create(rule_count);

    char *token = strtok(rule_lines, "\n|");
    while (token != NULL)
    {
        int key = atoi(token);
        token = strtok(NULL, "\n|");
        int value = atoi(token);
        token = strtok(NULL, "\n|");
        hash_table_entry *entry = hash_table_lookup(rule_set_hash_table, key);
        if (entry == NULL)
        {

            rule_set *value_ptr = (rule_set *)malloc(sizeof(rule_set));
            value_ptr->rules[0] = value;
            value_ptr->count = 1;
            hash_table_insert(rule_set_hash_table, key, value_ptr);
        }
        else
        {
            rule_set *value_ptr = entry->value;
            value_ptr->rules[value_ptr->count++] = value;
        }
    }

    printf("HT: %d\n", rule_set_hash_table->size);

    char *test_line = strtok(test_lines, "\n");
    int correct_num_sum = 0;
    int incorrect_num_sum = 0;
    int incorrect_numbers[100];
    int incorrect_numbers_count = 0;
    int line_num = 0;
    while (test_line != NULL)
    {
        int numbers[100];
        int numbers_count = parse_numbers_into_array(test_line, numbers);
        bool correct = true;
        for (int i = numbers_count - 1; i >= 0; i--)
        {
            hash_table_entry *entry = hash_table_lookup(rule_set_hash_table, numbers[i]);
            if (entry == NULL)
            {
                continue;
            }
            rule_set *rules_for_num = (rule_set *)(entry->value);
            for (int j = 0; j < i; j++)
            {
                for (int k = 0; k < rules_for_num->count; k++)
                {
                    if (rules_for_num->rules[k] == numbers[j])
                    {
                        if (correct)
                        {
                            correct = false;
                            printf("Line '%s' is incorrect: %d is before %d\n", test_line, numbers[j], numbers[i]);
                            incorrect_numbers[incorrect_numbers_count++]=line_num;
                        }
                    }
                }
            }
        }
        if (correct)
        {
            int middle_index = (numbers_count - 1) / 2;
            int middle_number = numbers[middle_index];
            printf("Line '%s' is CORRECT. Middle number=%d\n", test_line, middle_number);
            correct_num_sum += middle_number;
        }
        else
        {
            incorrect_num_sum+=sort_line_and_find_middle(numbers, numbers_count, rule_set_hash_table);
        }
        test_line = strtok(NULL, "\n");
        line_num++;
    }
    printf("Correct number sum: %d \n", correct_num_sum);

    test_line = strtok(test_lines, "\n");
    for(int i=0; i<incorrect_numbers_count;i++)
    {
        printf("Incorrect: %d\n",incorrect_numbers[i]);
    }
    return 0;
}