#include "helpers.h"
#include <math.h>

// Calculate the average value of the pixels
int average(int red, int green, int blue)
{
    float average = (red + green + blue) / 3.0;
    int round_average = round(average);

    return round_average;
}

// Calculate sepia value of given values
int sepia_calc(int red, int green, int blue, float red_multiplier,
               float green_multiplier, float blue_multiplier)
{
    float value = red_multiplier * red
                  + green_multiplier * green
                  + blue_multiplier * blue;

    if (value > 255)
    {
        return 255;
    }

    int round_value = round(value);

    return round_value;
}

// Calculate the sepia red value
int sepia_red(int red, int green, int blue)
{
    int value = sepia_calc(red, green, blue, 0.393, 0.769, 0.189);

    return value;
}

// Calculate the sepia green value
int sepia_green(int red, int green, int blue)
{
    int value = sepia_calc(red, green, blue, 0.349, 0.686, 0.168);

    return value;
}

// Calculate the sepia blue value
int sepia_blue(int red, int green, int blue)
{
    int value = sepia_calc(red, green, blue, 0.272, 0.534, 0.131);

    return value;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {   
            int red = image[h][w].rgbtRed;
            int green = image[h][w].rgbtGreen;
            int blue = image[h][w].rgbtBlue;

            int average_color = average(red, green, blue);

            image[h][w].rgbtRed = average_color;
            image[h][w].rgbtGreen = average_color;
            image[h][w].rgbtBlue = average_color;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int red = image[h][w].rgbtRed;
            int green = image[h][w].rgbtGreen;
            int blue = image[h][w].rgbtBlue;

            int red_value = sepia_red(red, green, blue);
            int green_value = sepia_green(red, green, blue);
            int blue_value = sepia_blue(red, green, blue);

            image[h][w].rgbtRed = red_value;
            image[h][w].rgbtGreen = green_value;
            image[h][w].rgbtBlue = blue_value;
        }
    }
    return;
}

// Reflect image horizontally
// it works by getting a pixel, then its opposite pixel,
// then inverts them
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int pixel = 0; pixel < (width / 2); pixel++)
        {
            int r_pixel_pos = width - 1 - pixel;

            RGBTRIPLE l_pixel = image[row][pixel];
            RGBTRIPLE r_pixel = image[row][r_pixel_pos];

            image[row][pixel] = r_pixel;
            image[row][r_pixel_pos] = l_pixel;
        }
    }
    return;
}

// puts into an array all the possible neighbors positions
// of a given pixel
void set_possibilities(int *length, int number, int limit, int positions[])
{
    if ((number - 1) < 0)
    {
        positions[0] = number;
        positions[1] = number + 1;
        *length = 2;
    }
    else if ((number + 1) > (limit - 1))
    {
        positions[0] = number - 1;
        positions[1] = number;
        *length = 2;
    }
    else
    {
        positions[0] = number - 1;
        positions[1] = number;
        positions[2] = number + 1;
        *length = 3;
    }
}

// putz into an array all neighbors of a given pixel and 
// given all possible neighbors positions
void get_pixels(int r_positions[], int c_positions[],
                int r_length, int c_length, int *pixels_amount,
                RGBTRIPLE pixels[], int height, int length,
                RGBTRIPLE image[height][length])
{
    int counter = 0;
    for (int r = 0; r < r_length; r++)
    {
        for (int c = 0; c < c_length; c++)
        {
            pixels[counter] = image[r_positions[r]][c_positions[c]];
            counter++;
        }
    }
    
    *pixels_amount = counter;
}

// calculate the average red amount of a given array of pixels
int average_red_amount(RGBTRIPLE pixels[], int length)
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += pixels[i].rgbtRed;   
    }
    
    int average = round((float)sum / length);
    return average;
}

// calculate the average green amount of a given array of pixels
int average_green_amount(RGBTRIPLE pixels[], int length)
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += pixels[i].rgbtGreen;   
    }
    
    int average = round((float)sum / length);
    return average;
}

// calculate the average blue amount of a given array of pixels
int average_blue_amount(RGBTRIPLE pixels[], int length)
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += pixels[i].rgbtBlue;   
    }
    
    int average = round((float)sum / length);
    return average;
}

// Blur image
// first, it creates a new image, using the "blurry" pixels,
// then, copies it to the original image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int r_length;
    int relative_r_pos[3];
    int c_length;
    int relative_c_pos[3];
    RGBTRIPLE pixels[9];
    int pixels_amount;
    RGBTRIPLE new_image[height][width];

    // setting the new image
    for (int r = 0; r < height; r++)
    {
        set_possibilities(&r_length, r, height, relative_r_pos);

        for (int c = 0; c < width; c++)
        {
            set_possibilities(&c_length, c, width, relative_c_pos);
            get_pixels(relative_r_pos, relative_c_pos, r_length, c_length,
                       &pixels_amount, pixels, height, width, image);
               
            int red = average_red_amount(pixels, pixels_amount);
            int green = average_green_amount(pixels, pixels_amount);
            int blue = average_blue_amount(pixels, pixels_amount);
            
            new_image[r][c].rgbtRed = red;
            new_image[r][c].rgbtGreen = green;
            new_image[r][c].rgbtBlue = blue;
        }
    }
    
    // copying the new image to the old image
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = new_image[r][c];
        }
    }
    
    image = new_image;
    return;
}

