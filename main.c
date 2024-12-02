
#include "days.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        printf("Usage: %s <day number>\n", argv[0]);
        return 1;
    }

    int day_number = atoi(argv[1]);
    switch(day_number)
    {
        case 1:
            day01("input_files/day01.txt");
            break;
        case 2:
            day02("input_files/day02.txt");
            break;
        case 3:
            day03("input_files/day03.txt");
            break;
        default:
            printf("Day %d not implemented.\n", day_number);
            return 1;
    }
}