
#include "days.h"

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
            day01();
            break;
        case 2:
            day02();
            break;
        default:
            printf("Day %d not implemented.\n", day_number);
            return 1;
    }
}