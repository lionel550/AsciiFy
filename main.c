#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include "stb_image.h"

void usage (char *program_name, FILE *stream)
{
    fprintf(stream, "Usage: %s [image_path]\n", program_name);
    fprintf(stream, "Usage: %s [commands]\n", program_name);
    fprintf(stream, "commands:\n");
    fprintf(stream, "    -h|--help            Display help.\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        usage(argv[0], stderr);
        return -1;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        usage(argv[0], stdout);
        return 0;
    }
    
    char *ascii_palette = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    int palette_size = (int) strlen(ascii_palette);

    int width, height, nbr_channels;
    int desired_channels = 1;

    unsigned char *pixels = stbi_load(argv[1], &width, &height, &nbr_channels, desired_channels);
    
    if (!pixels)
    {
        fprintf(stderr, "%s\n", stbi_failure_reason());
        return -1;
    }

    for (int i = 0; i < (height * width * desired_channels); i++)
    {
        if (i % width == 0)
        {
            printf("\n");
        }

        int index = (*(pixels + i) * (palette_size - 1)) / 255;
        printf("%c", ascii_palette[index]);
    }

    stbi_image_free(pixels);
    
    return 0;
}
