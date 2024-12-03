#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "util.h"
#include "days.h"

// TODO figure out how to use a C standard lib function to do this
int parse_int(char * input, int * output)
{
    int result = 0;
    int read_count = 0;
    while(*input!='\0' && isdigit(*input))
    {
        result = result*10 + (*input-'0');
        input++;
        read_count++;
    }
    *output = result;
    return read_count;
}

char * find_next_mul(char* input)
{
    return strstr(input, "mul(");
}


char * find_next_mul_with_toggle(char* input)
{
    while(1)
    {
        char* mul_index = strstr(input, "mul(");
        char* dont_index = strstr(input, "don't()");
        if(mul_index==NULL)
        {
            return NULL;
        }
        if(dont_index!=NULL && dont_index<mul_index)
        {
            input = strstr(dont_index, "do()");
            if(input==NULL)
            {
                return NULL;
            }
        }
        else{
            input = mul_index;
            break;
        }
    }
    return input;
}

void update_total(char*mul_instruction, int * total)
{
    mul_instruction+=4;
    int a;
    int b;
    int read_count = parse_int(mul_instruction, &a);
    mul_instruction+=read_count;
    if(read_count>0 && *mul_instruction==',')
    {
        mul_instruction++;
        read_count = parse_int(mul_instruction, &b);
        mul_instruction+=read_count;
        if(read_count>0 && *mul_instruction==')')
        {
            *total+=a*b;
        }
    }
}

int day03(char * file_name)
{
    char input[]="xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
    char * file_input = read_file(file_name);
    char * found = find_next_mul(file_input);
    int total = 0;
    while(found!=NULL)
    {
        update_total(found, &total);
        found = find_next_mul(found+1);
    }
    printf("Part1: %d\n", total);

    found = find_next_mul_with_toggle(file_input);
    total = 0;
    while(found!=NULL)
    {
        update_total(found, &total);
        found = find_next_mul_with_toggle(found+1);
    }
    printf("Part2: %d\n", total);

}