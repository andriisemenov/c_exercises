#include <stdio.h>
/* Example shows assigning a variable to a through pointer and then incrementing this value through the pointer. */
int main()
{
    int a = 0;
    int *p;
    p = &a;
    *p = 10;
    printf("%d\n", a);
    ++*p;
    printf("%d", a);
    return (0);
}