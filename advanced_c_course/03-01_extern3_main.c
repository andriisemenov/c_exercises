#include <stdio.h>

/*  Run gcc 03-01_extern3_main.c 03-01_extern3_manipulate.c  to compile both files
*   The only time external variables are reqiured is when working with structures in a function*/

void displayData(void);
void manipulateData(void);

int data[5] = {2, 3, 5, 7, 9};

int main()
{
    displayData();
    manipulateData();
    displayData();

    return (0);
}
