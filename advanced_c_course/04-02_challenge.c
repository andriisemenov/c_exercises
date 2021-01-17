#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 50
/*Using string.h lib here to get input and limit the input*/

int compare(const void *a, const void *b);

int main()
{
    char string_array[MAX_INPUT];
    int characters = 0;
    fgets(string_array, MAX_INPUT, stdin);
    characters = strlen(string_array);
    qsort(string_array, characters, sizeof(char), compare);
    printf("%s", string_array);
    return (0);
}

int compare(const void *a, const void *b)
{
    return (*(char *)a - *(char *)b);
}