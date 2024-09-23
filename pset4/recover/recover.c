#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    int size;
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    rewind(f);
    int filenumber = 0;
    int jpeg = 0;
    for (int i = 0; i < size / 512; i++)
    {
        BYTE *buffer = malloc(512 * sizeof(BYTE));
        fseek(f, 512 * i, SEEK_SET);
        if (fread(buffer, 512, 1, f) != 1)
        {
            free(buffer);
            return 0;
        }
        if ((int) buffer[0] == 0xff && (int) buffer[1] == 0xd8 && (int) buffer[2] == 0xff
            && ((int) buffer[3] & 0xf0) == 0xe0)
        {
            if (jpeg == 1)
            {
                filenumber++;
            }
            jpeg = 1;
            char *filename = malloc(8);
            sprintf(filename, "%03i.jpg", filenumber);
            FILE *img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);
            fclose(img);
            free(filename);
        }
        else if (jpeg == 1)
        {
            char *filename = malloc(8);
            sprintf(filename, "%03i.jpg", filenumber);
            FILE *img = fopen(filename, "a");
            fwrite(buffer, 512, 1, img);
            fclose(img);
            free(filename);
        }
        free(buffer);
    }
}