#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        printf("Height: ");
        h = get_int();
    }
    while (h < 0 || h > 23);      //For the limitation.

    int H;
    H = h;
    int counter = 0;
    for (int i = 0; i < H; i++)     //For building the hashs.
    {
        for (int j = 0; j < (h-1); j++)
        {
             if (h > 1)
             {
                printf(" ");
             }
        }
        for (int k = 0; k < (counter+1); k++)
        {
             printf("#");
        }

        printf("  ");
        for (int u = 0; u < (counter+1); u++)
        {
            printf("#");
        }

        printf("\n");
        h -= 1;
        counter += 1;
    }
}