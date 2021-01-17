#include <stdio.h>

int main()
{
    int number;
    printf("Enter an integer\n");
    scanf("%d", &number);
    printf("The floating point version is: %.1f", (float)number);
}