#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepR = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepG = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepB = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            if (sepR > 255)
            {
                sepR = 255;
            }

            if (sepG > 255)
            {
                sepG = 255;
            }

            if (sepB > 255)
            {
                sepB = 255;
            }

            image[i][j].rgbtRed = sepR;
            image[i][j].rgbtGreen = sepG;
            image[i][j].rgbtBlue = sepB;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image1[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0, k = 0, l = 1;
            int sumr = 0, sumg = 0, sumb = 0;
            int surr[18] = {-1, -1, -1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1, 0, 0};

            for (int m = 0; m < 9; m++)
            {
                if (((i + surr[k] >= 0) && (i + surr[k] < height)) && ((j + surr[l] >= 0) && (j + surr[l] < width)))
                {
                    sumr += image[i + surr[k]][j + surr[l]].rgbtRed;
                    sumg += image[i + surr[k]][j + surr[l]].rgbtGreen;
                    sumb += image[i + surr[k]][j + surr[l]].rgbtBlue;

                    count++;
                    k += 2;
                    l += 2;
                }

                else
                {
                    k += 2;
                    l += 2;
                }
            }

            image1[i][j].rgbtRed = round(sumr / (float) count);
            image1[i][j].rgbtGreen = round(sumg / (float) count);
            image1[i][j].rgbtBlue = round(sumb / (float) count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image1[i][j].rgbtRed;
            image[i][j].rgbtGreen = image1[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image1[i][j].rgbtBlue;
        }
    }

    return;
}
