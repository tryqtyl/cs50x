#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int average = round((image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed) / 3.0);
            image[row][col].rgbtBlue = average;
            image[row][col].rgbtGreen = average;
            image[row][col].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for(int col = 0; col < width / 2; col++)
        {
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][width - 1 - col];
            image[row][width - 1 - col] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create the temp variant so that the blurred pixel wont affect other pixels.
    RGBTRIPLE temp[height][width];
    // try to use the loop for coner and edge
    // for middle pixel, there are always -1, 0 and 1 to add
    for (int row = 0; row < height; row ++)
    {
        for (int col = 0; col < width; col ++)
        {
            float count = 0;
            int sumRed = 0;
            int sumBlue = 0;
            int sumGreen = 0;
            for (int i = -1; i < 2; i++)
            {
                // ignore first row
                if (row == 0 && i == -1)
                {
                    continue;
                }
                // ignore last row
                if (row == height - 1 && i == 1)
                {
                    continue;
                }
                for (int j = -1; j < 2; j++)
                {
                    // ignore first column
                    if (col == 0 && j == -1)
                    {
                        continue;
                    }
                    // ignore last column
                    if (col == width - 1 && j == 1)
                    {
                        continue;
                    }
                    sumBlue += image[row + i][col + j].rgbtBlue;
                    sumGreen += image[row + i][col + j].rgbtGreen;
                    sumRed += image[row + i][col + j].rgbtRed;
                    count++;
                }
            }
            temp[row][col].rgbtBlue = round(sumBlue / count);
            temp[row][col].rgbtGreen = round(sumGreen / count);
            temp[row][col].rgbtRed = round(sumRed / count);
        }
    }
    for (int row = 0; row < height; row ++)
    {
        for (int col = 0; col < width; col ++)
        {
            image[row][col] = temp[row][col];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int sobelx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int sobely[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int cnt = 0, gxBlue = 0, gxGreen = 0, gxRed = 0, gyBlue = 0, gyGreen = 0, gyRed = 0;
            for (int i = -1; i < 2; i++)
            {
                if (row + i < 0 || row + i > height - 1)
                {
                    continue;
                }
                for (int j = -1; j < 2; j++)
                {
                    if (col + j < 0 || col + j > width - 1)
                    {
                        continue;
                    }
                    gxBlue += sobelx[cnt] * image[row + i][col + j].rgbtBlue;
                    gyBlue += sobely[cnt] * image[row + i][col + j].rgbtBlue;
                    gxGreen += sobelx[cnt] * image[row + i][col + j].rgbtGreen;
                    gyGreen += sobely[cnt] * image[row + i][col + j].rgbtGreen;
                    gxRed += sobelx[cnt] * image[row + i][col + j].rgbtRed;
                    gyRed += sobely[cnt] * image[row + i][col + j].rgbtRed;
                    cnt++;
                }
            }
            temp[row][col].rgbtBlue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue)) > 255 ? 255 : round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            temp[row][col].rgbtGreen = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen)) > 255 ? 255 : round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            temp[row][col].rgbtRed = round(sqrt(gxRed * gxRed + gyRed * gyRed)) > 255 ? 255 : round(sqrt(gxRed * gxRed + gyRed * gyRed));
        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = temp[row][col];
        }
    }
    return;
}
