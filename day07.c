#include "days.h"
#include "util.h"
#include "hash_table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_OPERANDS 50

int sum(int *values, int value_count)
{
    int sum = 0;
    for (int i = 0; i < value_count; i++)
    {
        sum += values[i];
    }
    return sum;
}

int parse_operands(long operands[MAX_OPERANDS], char *input_line)
{
    int i = 0;
    int operand_count = 0;
    char *start = input_line;
    while (input_line[i] != '\0')
    {
        if (input_line[i] == ' ' || input_line[i] == '\0')
        {
            input_line[i] = '\0';
            int operand = atoi(start);
            operands[operand_count++] = operand;
            start = input_line + i + 1;
        }
        i++;
    }
    int operand = atoi(start);
    operands[operand_count++] = operand;
    start += i + 1;
    return operand_count;
}

long concat(long left, long right)
{
    char result_str[100];
    int count = sprintf(result_str, "%ld%ld", left, right);
    
    long result = atol(result_str);
    return result;
}

int calulate_combinations(long operands[MAX_OPERANDS], int operand_count, long target, int index, char operators[MAX_OPERANDS - 1])
{
    if (index >= operand_count)
    {

        printf("Invalid index: %d", index);
        exit(1);
    }
    if (index == operand_count - 1)
    {
        long total = operands[0];
        for (int i = 0; i < operand_count - 1; i++)
        {
            char operator= operators[i];
            long operand = operands[i+1];
            if (operator== '*')
            {
                total *= operand;
            }
            else if (operator== '+')
            {
                total += operand;
            }
            else if (operator=='|')
            {
                long result = concat(total, operand);
                total = result;
            }
            else
            {
                printf("Invalid operator: %c", operator);
                exit(1);
            }
        }
        if (total == target)
        {
            printf("%ld", operands[0]);
            for (int i = 0; i < operand_count - 1; i++)
            {
                printf("%c%ld", operators[i], operands[i+1]);
            }
            printf("=%ld\n", target);
            return 1;
        }
        return 0;
    }
    operators[index] = '*';
    int total = calulate_combinations(operands, operand_count, target, index + 1, operators);
    operators[index] = '|';
    total += calulate_combinations(operands, operand_count, target, index + 1, operators);
    operators[index] = '+';
    return total + calulate_combinations(operands, operand_count, target, index + 1, operators);
}

int day07(char *file_name)
{
    char *file_input = read_file(file_name);
    int length = strlen(file_input);

    char *line = strtok(file_input, "\n\0");
    long total_combinations = 0;
    long sum = 0;
    while (line != NULL)
    {
        long operands[MAX_OPERANDS];
        char operators[MAX_OPERANDS - 1];

        long target = atol(line);
        char *operand_str = strchr(line, ':') + 2;
        int operand_count = parse_operands(operands, operand_str);

        int valid_combinations = calulate_combinations(operands, operand_count, target, 0, operators);
        if (valid_combinations > 0)
        {
            sum += target;
        }
        long product = valid_combinations * target;
        // printf("Found: %d for target: %ld\n", valid_combinations, target);

        line = strtok(NULL, "\n\0");
    }
    printf("Valid combinations: %ld\n", total_combinations);
    printf("Sum combinations: %ld\n", sum);

    return 0;
}