#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Correct Usage\n");
        return 1;
    }
    FILE *fp = fopen(argv[1],"r");
    if (fp == NULL)
    {
        printf("Cant open the file\n");
        return 1;
    }
    int count = 0;
    int found = 0;
    BYTE *buffer = malloc(BLOCK_SIZE);
    char *filename = malloc(8);
    if (buffer == NULL || filename == NULL)
    {
        return 1;
    }
    FILE *img = NULL;
    while (fread(buffer, BLOCK_SIZE, 1, fp))
    {
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                count++;
                found = 1;
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                count++;
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
        }
        else if (found)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    fclose(fp);
    fclose(img);
    free(buffer);
    free(filename);
}