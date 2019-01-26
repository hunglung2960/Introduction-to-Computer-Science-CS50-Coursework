/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage Done
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize scale infile outfile\n");
        return 1;
    }

    // remember filenames Done
    char *infile = argv[2];
    char *outfile = argv[3];

    //TODO: get the scale
    double scale = atof(argv[1]);
    // open input file  Done
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file  Done
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
//-------------------------------------------------------------------------------------------------------------------------
    //TODO: determine padding for scanlines & update outfile's file size, image size, width and height for resizing.   Done
    //may use them back.
    int OldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int OldWidth = bi.biWidth;
    int OldHeight = bi.biHeight;
    bi.biWidth *= scale;
    bi.biHeight *= scale;
    int NewPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + NewPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    // write outfile's BITMAPFILEHEADER   Done
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER   Done
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
//------------------------------------------------------------------------------------------------------------------------------
    //TODO: To resize horizontally and vertically
    // iterate over infile's scanlines to get variables of color in an array called image
    RGBTRIPLE image[OldWidth][abs(OldHeight)];
    for (int i = 0; i < abs(OldHeight); i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < OldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            image[j][i] = triple;
        }

        fseek(inptr, OldPadding, SEEK_CUR);
    }
//-------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------
    //To copy to outfile from the array with resizing:
    int WidthLocator;
    int HeightLocator;
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            WidthLocator = j / scale;
            HeightLocator = i / scale;
            triple = image[WidthLocator][HeightLocator];
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        for (int k = 0; k < NewPadding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
