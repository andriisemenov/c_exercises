#include <stdio.h>
#include <stdlib.h>
#include "hysteresis.h"
#include <unistd.h>


#include <time.h>

int main(int argc, char **argv)
{
    
    srand(time(NULL));
    signed int input = 20;
    signed int previnput = 20;
    FILE *fp;

    fp = fopen("test.csv", "w+");
    printf("*************Random*********************\n");
    for(int i=0; i<=10000; i++)
    {
        
        int r = rand()%2;
        if(r)
        {
            input+=rand()%7;
        }
        else
        {
            input-=rand()%7;
        }
        if(input>100)
        {
            input = 100u;
        }
        else if(input<0)
        {
            input = 0u;
        }
        // hysteresis((unsigned int)input);
        fprintf(fp,"%d, %d ", input, hysteresis((unsigned int)input));
        fprintf(fp,"\n");
        // usleep(100000);
    }


    printf("*************Ascending*********************\n");
    for(int i=0; i<=100; i++)
    {

        printf("Input %d Output %d ", i, hysteresis(i));
        printf("\n");
    }
    printf("*******************Descending********************\n");
    for(int i=100; i>=0; i--)
    {
        printf("Input %d Output %d ", i, hysteresis(i));
        printf("\n");
    }

    printf("*******************Wobbly stuff********************\n");
    int h = 1;
    for(int i=0; i<=100; i++)
    {   
        int r = rand()%5;

        printf("Input %d Output %d ", 13+(r*h), hysteresis(13+(r*h)));
        h*=-1;
        printf("\n");
    }

    return (0);
}
