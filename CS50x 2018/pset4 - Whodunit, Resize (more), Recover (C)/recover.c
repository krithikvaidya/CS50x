#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    //Checking if the user has entered the input parameters correctly
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover <filename>\n");
        return 1;
    }

    //Opening the image for reading
    FILE* img = fopen(argv[1], "r");

    //Checking if file open is unsuccessful
    if(img == NULL)
    {
        fprintf(stderr, "Failed to open image file!\n");
        return 2;
    }

    //String to store filename of 7 characters
    char fileName[8];

    //Loop Control Variable
    int i = 0;

    //FILE pointer to work with each output .jpg file to be generated
    FILE* ptr = NULL;

    //Storage of each block of 512 bytes
    uint8_t bytes[512];

    while(1)
    {
        if(fread(bytes, 1, 512, img) == 0) //Simultaneously reads a block of data from the file and checks if no data has been read
            break;                         //If no data has been read, it means the EOF has been encountered, and fread return 0.

        //Checks if the first four bytes of the block matches with a JPEG file's first four bytes
        if(bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] >= 0xe0 && bytes[3] <= 0xef))
        {
            if(ptr != NULL) //If the first file hasn't been opened yet, ptr will be NULL.
                fclose(ptr);

            sprintf(fileName, "%03d.jpg", i); //fileName will now store the corresponding fileName.

            i++;

            ptr = fopen(fileName, "w");

            //Checking if file open is unsuccessful
            if(ptr == NULL)
            {
                fprintf(stderr, "Failed to open image file!\n");
                return 2;
            }

            fwrite(bytes, 1, 512, ptr);
        }

        else //If the block's first four bytes don't match with those of a JPEg file
        {
            if(i != 0)
                fwrite(bytes, 1, 512, ptr);

            else //If the first file hasn't been opened yet, keeping scanning the blocks till the first block of JPEG bytes is encountered
                continue;
        }
    }

    fclose(img);
}