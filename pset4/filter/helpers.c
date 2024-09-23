#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Correct
    // Take average of values
    float average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (round(image[i][j].rgbtRed) + round(image[i][j].rgbtGreen) + round(image[i][j].rgbtBlue)) / 3;
            // Assign average to each color value
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtBlue = round(average);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Correct
    // Temporoary variable for swapping
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Reflect each pixel on right side by swapping with left side
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Correct
    // Average color value variables
    int redaverage;
    int greenaverage;
    int blueaverage;
    int average;
    RGBTRIPLE tmplist[height][width];
    // Make copy of image for calculations
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmplist[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            redaverage = 0;
            greenaverage = 0;
            blueaverage = 0;
            average = 0;
            redaverage += tmplist[i][j].rgbtRed;
            greenaverage += tmplist[i][j].rgbtGreen;
            blueaverage += tmplist[i][j].rgbtBlue;
            average++;
            if (j - 1 > -1)
            {
                redaverage += tmplist[i][j - 1].rgbtRed;
                greenaverage += tmplist[i][j - 1].rgbtGreen;
                blueaverage += tmplist[i][j - 1].rgbtBlue;
                average++;
                if (i - 1 > -1)
                {
                    redaverage += tmplist[i - 1][j - 1].rgbtRed;
                    greenaverage += tmplist[i - 1][j - 1].rgbtGreen;
                    blueaverage += tmplist[i - 1][j - 1].rgbtBlue;
                    average++;
                }
            }
            if (i - 1 > -1)
            {
                redaverage += tmplist[i - 1][j].rgbtRed;
                greenaverage += tmplist[i - 1][j].rgbtGreen;
                blueaverage += tmplist[i - 1][j].rgbtBlue;
                average++;
                if (j + 1 < width)
                {
                    redaverage += tmplist[i - 1][j + 1].rgbtRed;
                    greenaverage += tmplist[i - 1][j + 1].rgbtGreen;
                    blueaverage += tmplist[i - 1][j + 1].rgbtBlue;
                    average++;
                }
            }
            if (j + 1 < width)
            {
                redaverage += tmplist[i][j + 1].rgbtRed;
                greenaverage += tmplist[i][j + 1].rgbtGreen;
                blueaverage += tmplist[i][j + 1].rgbtBlue;
                average++;
                if (i + 1 < height)
                {
                    redaverage += tmplist[i + 1][j + 1].rgbtRed;
                    greenaverage += tmplist[i + 1][j + 1].rgbtGreen;
                    blueaverage += tmplist[i + 1][j + 1].rgbtBlue;
                    average++;
                }
            }
            if (i + 1 < height)
            {
                redaverage += tmplist[i + 1][j].rgbtRed;
                greenaverage += tmplist[i + 1][j].rgbtGreen;
                blueaverage += tmplist[i + 1][j].rgbtBlue;
                average++;
                if (j - 1 > -1)
                {
                    redaverage += tmplist[i + 1][j - 1].rgbtRed;
                    greenaverage += tmplist[i + 1][j - 1].rgbtGreen;
                    blueaverage += tmplist[i + 1][j - 1].rgbtBlue;
                    average++;
                }
            }
            // Change the color calues of the pixels
            redaverage = round(round(redaverage) / average);
            image[i][j].rgbtRed = redaverage;
            greenaverage = round(round(greenaverage) / average);
            image[i][j].rgbtGreen = greenaverage;
            blueaverage = round(round(blueaverage) / average);
            image[i][j].rgbtBlue = blueaverage;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Correct
    // Making Gx vars for each color
    float GxRed;
    float GyRed;
    float GxGreen;
    float GyGreen;
    float GxBlue;
    float GyBlue;
    double redvalue;
    double greenvalue;
    double bluevalue;
    RGBTRIPLE tmplist[height][width];
    // Copy of image for calculations
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmplist[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Resetting Gx and Gy values
            GxRed = 0;
            GyRed = 0;
            GxGreen = 0;
            GyGreen = 0;
            GxBlue = 0;
            GyBlue = 0;
            // Calculations with the Gx and Gy kernels
            if (j - 1 > -1)
            {
                GxRed += tmplist[i][j - 1].rgbtRed * -2;
                GxGreen += tmplist[i][j - 1].rgbtGreen * -2;
                GxBlue += tmplist[i][j - 1].rgbtBlue * -2;
                GyRed += tmplist[i][j - 1].rgbtRed * 0;
                GyGreen += tmplist[i][j - 1].rgbtGreen * 0;
                GyBlue += tmplist[i][j - 1].rgbtBlue * 0;
                if (i - 1 > -1)
                {
                    GxRed += tmplist[i - 1][j - 1].rgbtRed * -1;
                    GxGreen += tmplist[i - 1][j - 1].rgbtGreen * -1;
                    GxBlue += tmplist[i - 1][j - 1].rgbtBlue * -1;
                    GyRed += tmplist[i - 1][j - 1].rgbtRed * -1;
                    GyGreen += tmplist[i - 1][j - 1].rgbtGreen * -1;
                    GyBlue += tmplist[i - 1][j - 1].rgbtBlue * -1;
                }
            }
            if (i - 1 > -1)
            {
                GxRed += tmplist[i - 1][j].rgbtRed * 0;
                GxGreen += tmplist[i - 1][j].rgbtGreen * 0;
                GxBlue += tmplist[i - 1][j].rgbtBlue * 0;
                GyRed += tmplist[i - 1][j].rgbtRed * -2;
                GyGreen += tmplist[i - 1][j].rgbtGreen * -2;
                GyBlue += tmplist[i - 1][j].rgbtBlue * -2;
                if (j + 1 < width)
                {
                    GxRed += tmplist[i - 1][j + 1].rgbtRed * 1;
                    GxGreen += tmplist[i - 1][j + 1].rgbtGreen * 1;
                    GxBlue += tmplist[i - 1][j + 1].rgbtBlue * 1;
                    GyRed += tmplist[i - 1][j + 1].rgbtRed * -1;
                    GyGreen += tmplist[i - 1][j + 1].rgbtGreen * -1;
                    GyBlue += tmplist[i - 1][j + 1].rgbtBlue * -1;
                }
            }
            if (j + 1 < width)
            {
                GxRed += tmplist[i][j + 1].rgbtRed * 2;
                GxGreen += tmplist[i][j + 1].rgbtGreen * 2;
                GxBlue += tmplist[i][j + 1].rgbtBlue * 2;
                GyRed += tmplist[i][j + 1].rgbtRed * 0;
                GyGreen += tmplist[i][j + 1].rgbtGreen * 0;
                GyBlue += tmplist[i][j + 1].rgbtBlue * 0;
                if (i + 1 < height)
                {
                    GxRed += tmplist[i + 1][j + 1].rgbtRed * 1;
                    GxGreen += tmplist[i + 1][j + 1].rgbtGreen * 1;
                    GxBlue += tmplist[i + 1][j + 1].rgbtBlue * 1;
                    GyRed += tmplist[i + 1][j + 1].rgbtRed * 1;
                    GyGreen += tmplist[i + 1][j + 1].rgbtGreen * 1;
                    GyBlue += tmplist[i + 1][j + 1].rgbtBlue * 1;
                }
            }
            if (i + 1 < height)
            {
                GxRed += tmplist[i + 1][j].rgbtRed * 0;
                GxGreen += tmplist[i + 1][j].rgbtGreen * 0;
                GxBlue += tmplist[i + 1][j].rgbtBlue * 0;
                GyRed += tmplist[i + 1][j].rgbtRed * 2;
                GyGreen += tmplist[i + 1][j].rgbtGreen * 2;
                GyBlue += tmplist[i + 1][j].rgbtBlue * 2;
                if (j - 1 > -1)
                {
                    GxRed += tmplist[i + 1][j - 1].rgbtRed * -1;
                    GxGreen += tmplist[i + 1][j - 1].rgbtGreen * -1;
                    GxBlue += tmplist[i + 1][j - 1].rgbtBlue * -1;
                    GyRed += tmplist[i + 1][j - 1].rgbtRed * 1;
                    GyGreen += tmplist[i + 1][j - 1].rgbtGreen * 1;
                    GyBlue += tmplist[i + 1][j - 1].rgbtBlue * 1;
                }
            }
            // Combining Gx and Gy into one value
            redvalue = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            if (redvalue > 255)
            {
                redvalue = 255;
            }
            greenvalue = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            if (greenvalue > 255)
            {
                greenvalue = 255;
            }
            bluevalue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            if (bluevalue > 255)
            {
                bluevalue = 255;
            }
            // Change Pixels
            image[i][j].rgbtRed = redvalue;
            image[i][j].rgbtGreen = greenvalue;
            image[i][j].rgbtBlue = bluevalue;
        }
    }
}
