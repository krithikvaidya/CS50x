// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int resize(float factor, FILE* inptr, FILE* outptr)
{
    FILE *temp;

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

    BITMAPFILEHEADER bf2 = bf;
    BITMAPINFOHEADER bi2 = bi;

    bi2.biWidth = (factor * bi.biWidth);
    bi2.biHeight = (factor * -bi.biHeight);

    bi2.biHeight = -bi2.biHeight;
    bf2.bfSize -= bi.biSizeImage;

    int padding_infile = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi2.biSizeImage -= padding_infile * abs(bi.biHeight);

    bi2.biSizeImage *= factor * factor;

    int padding_outfile = (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi2.biSizeImage += padding_outfile * abs(bi2.biHeight);

    bf2.bfSize += bi2.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);

    if(factor < 1)
    {
        int skip_factor = (int)(factor * 100);
        skip_factor = 100/skip_factor;

        //printf("\n%d\n", skip_factor);

        // iterate over infile's scanlines

        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight/skip_factor; i++)
        {
            if(i!=0)
            {
                for(int j = 0; j < skip_factor - 1; j++)
                    fseek(inptr, (bi.biWidth) * sizeof(RGBTRIPLE), SEEK_CUR);
            }

            //printf("\n%d\n%lu\n%d\n%d\n", -bi.biWidth, sizeof(RGBTRIPLE), padding_infile, skip_factor);
            //printf("\n%lu\n", (((-bi.biWidth) * sizeof(RGBTRIPLE)) - padding_infile)/skip_factor);

            for(int t = 0; t < (((bi.biWidth) * sizeof(RGBTRIPLE)) - padding_infile)/(skip_factor * sizeof(RGBTRIPLE)); t++)
            {
                RGBTRIPLE triple;

                //read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                //write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                if(t != (((bi.biWidth) * sizeof(RGBTRIPLE)) - padding_infile)/skip_factor - 1)
                    fseek(inptr, sizeof(RGBTRIPLE) * (skip_factor - 1), SEEK_CUR);
            }

            // skip over padding, if any
            fseek(inptr, padding_infile, SEEK_CUR);

            // then add it back
            for (int k = 0; k < padding_outfile; k++)
            {
                fputc(0x00, outptr);
            }
        }
        return 1;
    }

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for(int m = 0; m < factor; m++)
        {
            if(m != 0)
            fseek(inptr, ((-bi.biWidth) * sizeof(RGBTRIPLE)) - padding_infile, SEEK_CUR);


            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for(int counter = 0; counter < factor; counter++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }

            // skip over padding, if any
            fseek(inptr, padding_infile, SEEK_CUR);

            // then add it back
            for (int k = 0; k < padding_outfile; k++)
            {
                fputc(0x00, outptr);
            }
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);


    // success
    return 0;
}
int main(int argc, char *argv[])
{


    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize <factor> <sourcefile> <destinationfile>\n");
        return 1;
    }

    // remember factor and filenames
    float factor = atof(argv[1]);
    int fact = factor;
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    if(factor < 1)
        resize(factor, inptr, outptr);

    else if(factor - fact == 0)
        resize(factor, inptr, outptr);

    else
    {
        resize((int)factor*10, inptr, outptr);
        resize(0.1, inptr, outptr);
    }

    // success
    return 0;
}
