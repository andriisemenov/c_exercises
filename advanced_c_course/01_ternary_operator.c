#include <stdio.h>

int main(int argc, char **argv)
{
    int numb = 0;
    printf("Enter a number greater than 0\n");
    if (numb < 1)
    {
        numb = 1;
    }
    scanf("%d", &numb);
    printf("The number is %s", numb % 2 == 1 ? "odd" : "even");
    return (0);
}