#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
    char space = ' ';
    string Name = get_string();

    if (Name[0] != space)
    {
        printf("%c", toupper(Name[0]));                   //print out the initial if it is without space before it.

    }

    for (int i = 0; i < strlen(Name); i++)
    {

        if (Name[i-1] == space && Name[i] != space)     //find out the initials that are after spaces.
        {
            printf("%c", toupper(Name[i]));
        }
    }
    printf("\n");
    return 0;

}



