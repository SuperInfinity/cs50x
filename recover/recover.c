#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./recover filename\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Error opening the card..!\n");
        return 1;
    }

    uint8_t buffer[512];
    int filecount = -1;
    char filename[13];
    FILE *img = NULL;

    while (fread(buffer, 1, 512, card) == 512)
    {
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            filecount++;

            if (filecount == 0)
            {
                sprintf(filename, "%03i.jpg", filecount);

                img = fopen(filename, "w");

                fwrite(buffer, 1, 512, img);
            }

            else
            {
                fclose(img);

                sprintf(filename, "%03i.jpg", filecount);

                img = fopen(filename, "w");

                fwrite(buffer, 1, 512, img);
            }
        }

        else
        {
            if (filecount >= 0)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }

    fclose(card);
    fclose(img);

    return 0;
}
