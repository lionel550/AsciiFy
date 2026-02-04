#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "stb_image.h"

#define DISPLAY_WIDTH    80
#define DISPLAY_HEIGHT   24
#define MAX_PIXEL_VALUE  255

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
    
    char *ascii_palette = "@%#*+=-:. ";
    int palette_size = (int) strlen(ascii_palette);

    int width, height, nbr_channels;
    int desired_channels = 1;

    unsigned char *pixels = stbi_load(argv[1], &width, &height, &nbr_channels, desired_channels);
    
    if (!pixels)
    {
        fprintf(stderr, "%s\n", stbi_failure_reason());
        return -1;
    }

    double widthScale = (double) DISPLAY_WIDTH / width; 
    double heightScale = (double) DISPLAY_HEIGHT / height;

    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        for (int x = 0; x < DISPLAY_WIDTH; x++)
        {
            int originalX = (int) (x / widthScale);
            int originalY = (int) (y / heightScale);

            unsigned int value = pixels[(originalY * width) + originalX];
            int index = (value * (palette_size - 1)) / MAX_PIXEL_VALUE;

            printf("%c", ascii_palette[index]);
        }
        printf("\n");
    }

    stbi_image_free(pixels);
    
    return 0;
}
