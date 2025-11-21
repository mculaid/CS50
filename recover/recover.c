#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// reused my own submission id: 9343bb3
// https://github.com/me50/mculaid/blob/9343bb3f26a43bc51d8cca233c112c74f2d464d7/recover.c

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for correct input
    if (argc != 2)
    {
        printf("Usage: ./recover <file>\n");
        return 1;
    }

    // this is just the name of the file
    char *infile = argv[1];

    // open the file
    FILE *rawfile = fopen(infile, "r");

    // checking whether the file exists or not
    if (rawfile == NULL)
    {
        printf("File Not Found!\n");
        return 2;
    }

    // Size of a JPEG Block
    const int BLOCKSIZE = 512;
    // buffer for each block
    unsigned char buffer[BLOCKSIZE];
    // set image file pointer to Null;
    FILE *image = NULL;

    // QoL look for end of file
    fseek(rawfile, 0L, SEEK_END);
    // find size of the file
    int rawsize = ftell(rawfile);
    // find amount of blocks (filesize / 512)
    int rawblocks = rawsize / BLOCKSIZE; // will truncate uneven files
    // go back to beginning
    fseek(rawfile, 0L, SEEK_SET);

    int append = 1;
    // counter for images printed
    int counter = 0;
    // image name placeholder
    char defname[8];
    // main loop while amount of blocks > 0

    while (fread(buffer, BLOCKSIZE, 1, rawfile) == 1)
    {
        if (ftell(rawfile) <= rawsize)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] <= 0xef &&
                buffer[3] >= 0xe0)
            {
                // always close image before opening a new one except the first time
                if (counter > 0)
                {
                    fclose(image);
                }
                sprintf(defname, "%03i.jpg", counter);
                image = fopen(defname, "w");
                counter++;
                fwrite(buffer, BLOCKSIZE, 1, image);
            }
            else
            {
                if (image != NULL)
                {
                    fwrite(buffer, BLOCKSIZE, 1, image);
                }
            }
        }
    }

    fclose(rawfile);
    fclose(image);
    return 0;
}
