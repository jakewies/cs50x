    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // read scanline size times
        for (int k = 0; j < size; j++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile size times
                for (int s = 0; s < size; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                
                // add padding if necessary
                for (int p = 0; p < padding; k++)
                {
                    fputc(0x00, outptr);
                }
                
                // jump back to beginning of scanline to resize vertically to fulfill size
                if (k < size - 1)  
                {
                    fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
                }
            }    
        }
                 
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }
    
    
