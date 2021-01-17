#include <stdio.h>

int main(int argc, char **argv)
{

    printf("The program name is %s\n", argv[0]);
    printf("There were %d command line arguments\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("Arg %d is: %s\n", i, argv[i]);
    }
    return (0);
}