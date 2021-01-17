#include <stdio.h>

int main()
{
    int a = 0;
    int *p;
    *p = 10;
    a = *p;
    printf("%d\n", a);
    ++*p;
    a = *p;
    printf("%d", a);
    return (0);
}