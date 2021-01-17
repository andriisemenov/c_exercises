#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_INPUT 30

struct person
{
    char name[MAX_NAME_INPUT];
    int age;
};

struct person *allocateStruct(void);
void fillStruct(struct person *p);
void displayStruct(struct person *p);

int main(void)
{
    struct person *user;
    user = allocateStruct();
    fillStruct(user);
    displayStruct(user);
    return (0);
}

struct person *allocateStruct(void)
{
    struct person *p;

    p = (struct person *)malloc(sizeof(struct person));
    if (p == NULL)
    {
        perror("Unable to allocate structure");
        exit(1);
    }
    return (p);
}

void fillStruct(struct person *p)
{
    int age;
    char string_array[MAX_NAME_INPUT];
    printf("Enter user name\n");
    fgets(string_array, MAX_NAME_INPUT, stdin);
    strcpy(p->name, string_array);
    printf("Enter user age\n");
    scanf("%d", &p->age);
}

void displayStruct(struct person *p)
{
    printf("User name: %s", p->name);
    printf("User age: %d", p->age);
}