/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <stdint.h>

#define BLOCK 512

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{        
    // open CF card
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }
    
    // create buffer storage of size 512 bytes & filename storage
    BYTE buffer[BLOCK];
    char filename[8];
    
    // define jpg outfile, if jpg has been found & how many
    FILE* img;
    bool jpg = false;
    int file_counter = 0;
    
    // iterate over CF Card
    while (fread(buffer, BLOCK, 1, file) != 0)
    {    
        // check first 4 bytes of block for signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff 
        && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // name the file
            sprintf(filename, "%03d.jpg", file_counter);
                        
            if (jpg)
            {
                // close current jpg, open new, and append block
                fclose(img);               
                img = fopen(filename, "a");
                fwrite(buffer, BLOCK, 1, img);
                
                // update counter
                file_counter++;
            } 
            else if (!jpg)
            {
                // open new jpg and append block
                img = fopen(filename, "a");
                fwrite(buffer, BLOCK, 1, img);
                
                // set jpg found to true & update counter
                jpg = true;
                file_counter++;
            }   
        }
        // if no signature was found but jpg is true 
        else if (jpg)
        { 
            // append to jpg file
            fwrite(buffer, BLOCK, 1, img);     
        }
    }
    
    // close last jpg
    if (img)
    {
        fclose(img); 
    }    
    
    // close CF card
    fclose(file);
    
    return 0;
}
