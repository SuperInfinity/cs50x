#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate thro the Matrix-image:
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // taking average of all the pixel values and replacing all of them to the same..!
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
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

    // iterate thro the pixels::

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float sumr = 0.0, sumg = 0.0, sumb = 0.0;

            // array of 3x3 area of the pixels;
            int surr[18] = {-1, -1, -1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1, 0, 0};
            int k = 0, l = 1;

            // check for the surrounding pixels...!!
            for (int m = 0; m < 9; m++)
            {
                if ((((i + surr[k]) >= 0) && ((i + surr[k]) < height)) && (((j + surr[l]) >= 0) && ((j + surr[l]) < width)))
                {
                    sumb += image[i + surr[k]][j + surr[l]].rgbtBlue;
                    sumg += image[i + surr[k]][j + surr[l]].rgbtGreen;
                    sumr += image[i + surr[k]][j + surr[l]].rgbtRed;

                    k += 2;
                    l += 2;

                    count++;
                }

                else
                {
                    k += 2;
                    l += 2;
                }
            }

            sumr = round(sumr / count);
            sumg = round(sumg / count);
            sumb = round(sumb / count);

            if (sumr > 255)
            {
                sumr = 255;
            }

            if (sumg > 255)
            {
                sumg = 255;
            }

            if (sumb > 255)
            {
                sumb = 255;
            }

            image1[i][j].rgbtBlue = sumb;
            image1[i][j].rgbtGreen = sumg;
            image1[i][j].rgbtRed = sumr;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image1[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image1[i][j].rgbtGreen;
            image[i][j].rgbtRed = image1[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image1[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int l = 0, k = 1;
            int sumr = 0, sumg = 0, sumb = 0;
            int sumrx = 0, sumgx = 0, sumbx = 0;
            int sumry = 0, sumgy = 0, sumby = 0;
            int surr[18] = {-1, -1, -1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1, 0, 0};
            int Gx[9] = {-1, 0, 1, 2, 1, 0, -1, -2, 0};
            int Gy[9] = {-1, -2, -1, 0, 1, 2, 1, 0, 0};

            for (int m = 0; m < 9; m++)
            {

                if ((((i + surr[l]) >= 0) && ((i + surr[l]) < height)) && (((j + surr[k]) >= 0) && ((j + surr[k]) < width)))
                {
                    // for Gx;
                    sumbx += ((image[i + surr[l]][j + surr[k]].rgbtBlue) * Gx[m]);
                    sumgx += ((image[i + surr[l]][j + surr[k]].rgbtGreen) * Gx[m]);
                    sumrx += ((image[i + surr[l]][j + surr[k]].rgbtRed) * Gx[m]);

                    // for Gy:
                    sumby += ((image[i + surr[l]][j + surr[k]].rgbtBlue) * Gy[m]);
                    sumgy += ((image[i + surr[l]][j + surr[k]].rgbtGreen) * Gy[m]);
                    sumry += ((image[i + surr[l]][j + surr[k]].rgbtRed) * Gy[m]);

                    l += 2;
                    k += 2;
                }

                else
                {
                    l += 2;
                    k += 2;
                }
            }

            // combine the Gx and Gy:
            sumbx = sumbx * sumbx;
            sumby = sumby * sumby;
            sumgx = sumgx * sumgx;
            sumgy = sumgy * sumgy;
            sumrx = sumrx * sumrx;
            sumry = sumry * sumry;

            sumb = round(sqrt(sumbx + sumby));
            sumg = round(sqrt(sumgx + sumgy));
            sumr = round(sqrt((sumrx + sumry)));

            if (sumb > 255)
            {
                sumb = 255;
            }

            if (sumg > 255)
            {
                sumg = 255;
            }

            if (sumr > 255)
            {
                sumr = 255;
            }

            image1[i][j].rgbtBlue = sumb;
            image1[i][j].rgbtGreen = sumg;
            image1[i][j].rgbtRed = sumr;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image1[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image1[i][j].rgbtGreen;
            image[i][j].rgbtRed = image1[i][j].rgbtRed;
        }
    }

    return;
}
