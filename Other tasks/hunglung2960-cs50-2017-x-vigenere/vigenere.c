#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    //stop the program when argument count is not 2.
    if (argc != 2)
    {
        printf("Key is wrong.\n");
        return 1;
    }

    //get the key and make sure they are alphabets.
    string key = argv[1];
    for (int j = 0; j < strlen(key); j++)
    {
        if (key[j] < 65 || (key[j] > 90 && key[j] < 97) || key[j] > 122)
        {
            printf("Key is wrong.\n");
            return 1;
        }
    }

    //get the plaintext.
    string plaintext = get_string("plaintext: ");


    int k;
    //indicate here is ciphertext.
    printf("ciphertext: ");
    //iterate every letter in the plaintext.
    for (int i = 0; i < strlen(plaintext); i++)
    {
        //change string key to integer key(only for upper case).
        if (key[i % (strlen(key))] >= 65 && key[(strlen(key))] <= 90)
        {
            k = (((int)key[i % (strlen(key))]) - 65);
        }
        //change string key to integer key(only for lower case).
        if (key[i % (strlen(key))] >= 97 && key[(strlen(key))] <= 122)
        {
            k = (((int)key[i % (strlen(key))]) - 97);
        }


        //let those characters that are not letters stay the same.
        if ((plaintext[i] > 90 && plaintext[i] < 97) || plaintext[i] < 65 || plaintext[i] > 122)
        {
            printf("%c", plaintext[i]);
        }
        //wrap around from the back to the front when ciphertext out of bound of letters.
        else if (plaintext[i] + (k % 26) > 90 && plaintext[i] <= 90 && plaintext[i] >= 65)
        {
            printf("%c", (plaintext[i] - (26 - (k % 26))));
        }
        else if (plaintext[i] + (k % 26) > 122 && plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            printf("%c", (plaintext[i] - (26 - (k % 26))));
        }
        //cipher the letters that will not be out of bound after ciphering.
        else
        {
            printf("%c", (plaintext[i] + (k % 26)));
        }
    }
    printf("\n");
    return 0;

}