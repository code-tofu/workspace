#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int grayscale = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);//int/int
            image[i][j].rgbtRed = grayscale;
            image[i][j].rgbtBlue = grayscale;
            image[i][j].rgbtGreen = grayscale;
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
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < (height) ; i++)
    {
        for (int j = 0; j < (width / 2) ; j++) // in odd pixel cases we swap until center - 1 and don't swap centre
        {
            RGBTRIPLE swap; //must declaring before using memebrs
            swap.rgbtRed = image[i][j].rgbtRed;
            swap.rgbtBlue = image[i][j].rgbtBlue;
            swap.rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - (j + 1)].rgbtRed; //should be (j + 1) instead of j beacuse of zero index
            image[i][j].rgbtBlue = image[i][width - (j + 1)].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - (j + 1)].rgbtGreen;
            image[i][width - (j + 1)].rgbtRed = swap.rgbtRed;
            image[i][width - (j + 1)].rgbtBlue = swap.rgbtBlue;
            image[i][width - (j + 1)].rgbtGreen = swap.rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make temp array
    // CANNOT MODIFY THE ARRAY DIRECTLY AS THE CHANGES PROPAGATES
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    //center cases first
    for (int i = 1; i < (height - 1); i++)
    {
        for (int j = 1; j < (width - 1); j++)
        {
            int sumRed = 0, sumBlue = 0, sumGreen = 0;
            for (int k = (i - 1); k < (i + 2); k++)
            {
                for (int l = (j - 1); l < (j + 2); l++)
                {
                    sumRed += temp[k][l].rgbtRed;
                    sumBlue += temp[k][l].rgbtBlue;
                    sumGreen += temp[k][l].rgbtGreen;
                }
            }
            image[i][j].rgbtRed = round(sumRed / 9.0); //9 pixels total
            image[i][j].rgbtBlue = round(sumBlue / 9.0); //int/int
            image[i][j].rgbtGreen = round(sumGreen / 9.0);
        }
    }

    //edge cases
    for (int i = 1; i < (height - 1); i++) //j = 1 //note i terminted with previous loop
    {
        int j = 0;
        int sumRed = 0, sumBlue = 0, sumGreen = 0;
        for (int k = (i - 1); k < (i + 2); k++)
        {
            sumRed += temp[k][j].rgbtRed; //don't forget type additions limited by 255?
            sumRed += temp[k][j + 1].rgbtRed;
            sumBlue += temp[k][j].rgbtBlue;
            sumBlue += temp[k][j + 1].rgbtBlue;
            sumGreen += temp[k][j].rgbtGreen;
            sumGreen += temp[k][j + 1].rgbtGreen;
        }
        image[i][j].rgbtRed = round(sumRed / 6.0); //6 pixels total
        image[i][j].rgbtBlue = round(sumBlue / 6.0);
        image[i][j].rgbtGreen = round(sumGreen / 6.0);

        j = width - 1;
        sumRed = sumBlue = sumGreen = 0;
        for (int k = (i - 1); k < (i + 2); k++)
        {
            sumRed += temp[k][j].rgbtRed;
            sumRed += temp[k][j - 1].rgbtRed;
            sumBlue += temp[k][j].rgbtBlue;
            sumBlue += temp[k][j - 1].rgbtBlue;
            sumGreen += temp[k][j].rgbtGreen;
            sumGreen += temp[k][j - 1].rgbtGreen;
        }
        image[i][j].rgbtRed = round(sumRed / 6.0); //6 pixels total
        image[i][j].rgbtBlue = round(sumBlue / 6.0);
        image[i][j].rgbtGreen = round(sumGreen / 6.0);
    }

    for (int j = 1; j < (width - 1); j++) //i = 1
    {
        int i = 0;
        int sumRed = 0, sumBlue = 0, sumGreen = 0;
        for (int k = (j - 1); k < (j + 2); k++)
        {
            sumRed += temp[i][k].rgbtRed; //don't forget type additions limited by 255?
            sumRed += temp[i + 1][k].rgbtRed;
            sumBlue += temp[i][k].rgbtBlue;
            sumBlue += temp[i + 1][k].rgbtBlue;
            sumGreen += temp[i][k].rgbtGreen;
            sumGreen += temp[i + 1][k].rgbtGreen;
        }
        image[i][j].rgbtRed = round(sumRed / 6.0); //6 pixels total
        image[i][j].rgbtBlue = round(sumBlue / 6.0);
        image[i][j].rgbtGreen = round(sumGreen / 6.0);

        i = height - 1;
        sumRed = sumBlue = sumGreen = 0;
        for (int k = (j - 1); k < (j + 2); k++)
        {
            sumRed += temp[i][k].rgbtRed;
            sumRed += temp[i - 1][k].rgbtRed;
            sumBlue += temp[i][k].rgbtBlue;
            sumBlue += temp[i - 1][k].rgbtBlue;
            sumGreen += temp[i][k].rgbtGreen;
            sumGreen += temp[i - 1][k].rgbtGreen;
        }
        image[i][j].rgbtRed = round(sumRed / 6.0); //6 pixels total
        image[i][j].rgbtBlue = round(sumBlue / 6.0);
        image[i][j].rgbtGreen = round(sumGreen / 6.0);
    }

    // //corner cases
    int sumRed = 0, sumBlue = 0, sumGreen = 0, i = 0, j = 0;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            sumRed += temp[i][j].rgbtRed;
            sumBlue += temp[i][j].rgbtBlue;
            sumGreen += temp[i][j].rgbtGreen;
        }
    }
    image[0][0].rgbtRed = round(sumRed / 4.0);
    image[0][0].rgbtBlue = round(sumBlue / 4.0);
    image[0][0].rgbtGreen = round(sumGreen / 4.0);

    sumRed = sumBlue = sumGreen = 0;
    for (i = (height - 1); i > (height - 3); i--)
    {
        for (j = 0; j < 2; j++)
        {
            sumRed += temp[i][j].rgbtRed;
            sumBlue += temp[i][j].rgbtBlue;
            sumGreen += temp[i][j].rgbtGreen;
        }
    }
    image[height - 1][0].rgbtRed = round(sumRed / 4.0);
    image[height - 1][0].rgbtBlue = round(sumBlue / 4.0);
    image[height - 1][0].rgbtGreen = round(sumGreen / 4.0);

    sumRed = sumBlue = sumGreen = 0;
    for (i = 0; i < 2; i++)
    {
        for (j = (width - 1); j > (width - 3); j--)
        {
            sumRed += temp[i][j].rgbtRed;
            sumBlue += temp[i][j].rgbtBlue;
            sumGreen += temp[i][j].rgbtGreen;
        }
    }
    image[0][width - 1].rgbtRed = round(sumRed / 4.0);
    image[0][width - 1].rgbtBlue = round(sumBlue / 4.0);
    image[0][width - 1].rgbtGreen = round(sumGreen / 4.0);

    sumRed = sumBlue = sumGreen = 0;
    for (i = (height - 1); i > (height - 3); i--)
    {
        for (j = (width - 1); j > (width - 3); j--)
        {
            sumRed += temp[i][j].rgbtRed;
            sumBlue += temp[i][j].rgbtBlue;
            sumGreen += temp[i][j].rgbtGreen;
        }
    }
    image[height - 1][width - 1].rgbtRed = round(sumRed / 4.0);
    image[height - 1][width - 1].rgbtBlue = round(sumBlue / 4.0);
    image[height - 1][width - 1].rgbtGreen = round(sumGreen / 4.0);

    return;
}


