#include <stdio.h>
/*  A program generating primes and showcasing pointer returning function
*   The key is to define a pointer variable of a type used in the array
*   and then to assign the result of the pointer returning function to this variable(pointer)*/

#define PRIMES_NUM 5

int *getPrimes(void)
{
    static int primes[PRIMES_NUM];
    int count, i = 3, c, index = 0;
    primes[index] = 2;
    index++;
    for (count = 2; count <= sizeof(primes) / sizeof(int);)
    {
        for (c = 2; c <= i - 1; c++)
        {
            if (i % c == 0)
                break;
        }
        if (c == i)
        {
            primes[index] = i;
            index++;
            count++;
        }
        i++;
    }
    return primes;
}

int main()
{
    printf("%d prime numbers: \n", PRIMES_NUM);
    int *primes;
    primes = getPrimes();
    for (int i = 0; i < PRIMES_NUM; i++)
    {
        printf("%d ", primes[i]);
    }
    printf("\n");

    return (0);
}