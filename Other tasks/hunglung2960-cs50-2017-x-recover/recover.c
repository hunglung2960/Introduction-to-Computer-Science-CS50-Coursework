#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>


typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    //Ensure proper usage.
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    //Get in the image file.
    char *image = argv[1];
    //Open the image file.
    FILE *inptr = fopen(argv[1], "r");
    //Error if the image cannot be opened.
    if (inptr == NULL)
    {
        fprintf(stderr, "Cannot open %s.\n", image);
        return 2;
    }
    FILE *img = NULL;
    char filename[8];
    int number = 0;
    BYTE buffer[512];
    int JPEGFOUND = 0;//<< 0 means not found / 1 means found
    while (fread(buffer, 512, 1, inptr) == 1)
    {
        //Read the image file. (1 block = 512 bytes)
        //fread(buffer, 1, 512, inptr); // Decided 512 block & each block = 1 bytes as the end of file occur bytes <= 512 bytes

        //Start of a jpeg?
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)  //do not understand......
        {
            //print out the jpeg found.
            sprintf(filename, "%03i.jpg", number);
            img = fopen(filename, "w");
            number += 1;
            JPEGFOUND = 1;
        }
        if(JPEGFOUND == 1)
        {
            fwrite(buffer, 512, 1, img);
        }


    }



    fclose(img);
    fclose(inptr);

    return 0;

}


