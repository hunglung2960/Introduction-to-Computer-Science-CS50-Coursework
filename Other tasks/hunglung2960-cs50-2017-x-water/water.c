#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Minutes: ");
    int minutes = get_int();
    while (minutes < 0)
    {
        printf("Error.Please do not input negative value.\n");
        printf("Please retyoe.\n");
        printf("Minutes: ");
        minutes = get_int();
    }
    if (minutes >= 0)
    {
        int n;
        printf("Bottles: %i\n", n = minutes * 12);
    }
}