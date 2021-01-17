#include <stdio.h>
#include <string.h>

/*Outputting a string using pointer math*/

#define MAX_INPUT 30

int main(void)
{
    char *text = "Hello, this is Andrii\n"; //Alternative way. Then text can be used directly as a pointer
    char *ps;
    int characters = 0;
    char string_array[MAX_INPUT];
    fgets(string_array, MAX_INPUT, stdin);
    characters = strlen(string_array);
    ps = string_array;
    for (int i = 0; i < characters; i++)
    {
        printf("%c", *(ps + i));
    }
    return (0);
}