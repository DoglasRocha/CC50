// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// define BYTE
typedef uint8_t BYTE;
typedef int16_t SAMPLE;

// Number of BYTEs in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    BYTE header[HEADER_SIZE];
    int BYTEs_read = fread(&header, sizeof(BYTE), HEADER_SIZE, input);
    if (BYTEs_read == HEADER_SIZE)
    {
        fwrite(&header, sizeof(BYTE), HEADER_SIZE, output);
    }
    else
    {
        printf("Could not read header from input file. \n");
        return 1;
    }

    //  Read SAMPLEs from input file and write updated data to output file
    SAMPLE buffer;
    while (fread(&buffer, sizeof(SAMPLE), 1, input) == 1)
    {
        buffer = factor * buffer;
        fwrite(&buffer, sizeof(SAMPLE), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
