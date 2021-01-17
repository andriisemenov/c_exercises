#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* To use toupper() function include <ctype.h> */

#define MAX_INPUT 50

void convert(char *a);

int main(void)
{
    int characters = 0;
    char string_array[MAX_INPUT];
    fgets(string_array, MAX_INPUT, stdin);
    characters = strlen(string_array);
    convert(string_array);
    printf("%s", string_array);
    return (0);
}

void convert(char *a)
{
    while (*a)
    {
        *a = toupper(*a);
        if (*a == ' ')
        {
            *a = '_';
        }
        a++;
    }
}