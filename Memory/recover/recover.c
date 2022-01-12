// DISCLAIMER: The code does everything that it should do. The 49 images
// are recovered. But, check50 says that it does not succeed due to segmentation
// fault. I have run valgrind and it does not found any memory related error.
// Because of that, I am submitting the code with the errors, I could not
// find out where the errors are thrown.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

// hints the compiler that this function is gonna be implemented later
bool is_jpg_beggining(BYTE buffer[]);


int main(int argc, char *argv[])
{
    // checks if the program has been "summoned" correctly
    if (argc != 2)
    {
        printf("Usage: ./recover filename.raw");
        return 1;
    }

    // opens the raw file
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        return 1;
    }
    
    bool is_writing = false;
    int files_written = 0;
    char file_name[15];

    sprintf(file_name, "images/%03i.jpg", files_written);
    FILE *new_file = fopen(file_name, "a");

    BYTE buffer[512];
    while (fread(buffer, sizeof(BYTE), 512, raw_file) == 512)
    {
        // if is the beggining of the jpg and it is the first found, 
        // the program begins writing the files
        // if it is not the first round and found a jpg beggining,
        // close the current file, update the name and open/create a
        // new file.
        // if its not the beggining of a file but it is writing, just
        // keep writing
        if (is_jpg_beggining(buffer))
        {
            if (is_writing)
            {
                fclose(new_file);
                files_written++;
                sprintf(file_name, "images/%03i.jpg", files_written);
                
                new_file = fopen(file_name, "a");
                fwrite(buffer, sizeof(BYTE), 512, new_file);
            }
            else
            {
                fwrite(buffer, sizeof(BYTE), 512, new_file);
                is_writing = true;
            }
        }
        else
        {
            if (is_writing)
            {
                fwrite(buffer, sizeof(BYTE), 512, new_file);
            }
        }    
    }
    
    fclose(new_file);
    fclose(raw_file);
    return 0;
}

// return if it is the beggining of a jpg
bool is_jpg_beggining(BYTE buffer[])
{
    return (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0);
}