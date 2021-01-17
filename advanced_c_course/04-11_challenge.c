#include <stdio.h>

/*  Sorting an array of struct, bubble sort 
*   How to do it with qsort?*/

#define SIZE 7

int main()
{
    struct weather
    {
        char day[10];
        float temp;
    };
    struct weather week[SIZE] = {
        {"Sunday", 72.5},
        {"Monday", 68.4},
        {"Tuesday", 75.0},
        {"Wednesday", 73.8},
        {"Thursday", 65.1},
        {"Friday", 72.8},
        {"Saturday", 75.2}};

    /* Sort the array by temperatre*/
    for (int outer = 0; outer < SIZE; outer++)
        for (int inner = outer + 1; inner < SIZE; inner++)
        {
            if (week[outer].temp > week[inner].temp)
            {
                struct weather temp = week[inner];
                week[inner] = week[outer];
                week[outer] = temp;
            }
        }

    puts("This week's forecast:");
    for (int x = 0; x < 7; x++)
        printf("%10s %.1f degrees\n",
               week[x].day,
               week[x].temp);

    return (0);
}
