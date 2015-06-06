/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes 24-bit uncompressed BMPs by a factor of n.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // convert argv[1] to an int
    int size = atoi(argv[1]);

    // ensure n is positive int <= 100
    if (size < 1 || size > 100)
    {
        printf("n, the resize factor, must satisfy 0 < n <= 100\n");
        return 2;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
        return 5;
    }

    /**** UPDATE BMP OUTFILE HEADER INFO  ****/
    BITMAPFILEHEADER bf_Out = bf;
    BITMAPINFOHEADER bi_Out = bi;

    bi_Out.biHeight = bi.biHeight * size; 
    bi_Out.biWidth = bi.biWidth * size;

    // determine padding for I/0 scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_Out = (4 - (bi_Out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi_Out.biSizeImage = abs(bi_Out.biHeight) * (bi_Out.biWidth * sizeof(RGBTRIPLE) + padding_Out);
    bf_Out.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi_Out.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_Out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_Out, sizeof(BITMAPINFOHEADER), 1, outptr);

    /**** RESIZE IMAGE ****/

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // read scanline size times
        for (int k = 0; k < size; k++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile size times
                for (int s = 0; s < size; s++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
                // add padding if necessary
                for (int p = 0; p < padding_Out; p++)
                {
                    fputc(0x00, outptr);
                }

                // jump back to beginning of scanline to resize vertically to fulfill size
                if (k < size - 1)
                {
                    fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
                }
        }
        
        // skip over padding, if necessary
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
