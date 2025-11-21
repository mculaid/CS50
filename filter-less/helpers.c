#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Reused my previous code from my own submission 6f32318
// https://github.com/me50/mculaid/blob/c25b6caf9aae6ec1220789be1e9e806d5c9c7a27/helpers.c

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // we go from left to right and we repeat that height times
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float mongo = 3.00;
            double temp =
                round((image[h][w].rgbtRed + image[h][w].rgbtBlue + image[h][w].rgbtGreen) / mongo);
            image[h][w].rgbtRed = image[h][w].rgbtBlue = image[h][w].rgbtGreen = temp;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (h < height && w < width)
            {
                int red = ((round((0.393 * image[h][w].rgbtRed) + (0.769 * image[h][w].rgbtGreen) +
                                  (0.189 * image[h][w].rgbtBlue))));
                int green =
                    ((round((0.349 * image[h][w].rgbtRed) + (0.686 * image[h][w].rgbtGreen) +
                            (0.168 * image[h][w].rgbtBlue))));
                int blue = ((round((0.272 * image[h][w].rgbtRed) + (0.534 * image[h][w].rgbtGreen) +
                                   (0.131 * image[h][w].rgbtBlue))));
                if (blue > 255)
                {
                    blue = 255;
                }
                if (red > 255)
                {
                    red = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                image[h][w].rgbtRed = red;
                image[h][w].rgbtGreen = green;
                image[h][w].rgbtBlue = blue;
            }
            else
            {
                break;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // outer loop + save to temp in arranged order
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp[h][width - w - 1] = image[h][w];
        }
    }
    // overwrite old file with temp
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = temp[h][w];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // main loop
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float counter = 0.00;
            float goalred = 0, goalgreen = 0, goalblue = 0;
            int x, y, a, b;

            // tL
            if (h == 0 && w == 0)
            {
                x = 0, y = 0, a = 2, b = 2;
            }
            // bL
            else if ((h == height - 1) && (w == 0))
            {
                x = -1, y = 0, a = 1, b = 2;
            }
            // tR
            else if ((h == 0) && (w == width - 1))
            {
                x = 0, y = -1, a = 2, b = 1;
            }
            // bR
            else if ((h == height - 1) && (w == width - 1))
            {
                x = -1, y = -1, a = 1, b = 1;
            }
            // left side OK
            else if (w == 0)
            {
                x = -1, y = 0, a = 2, b = 2;
            }
            // right side OK
            else if (w == width - 1)
            {
                x = -1, y = -1, a = 2, b = 1;
            }
            // top row OK
            else if (h == 0)
            {
                x = 0, y = -1, a = 2, b = 2;
            }
            // bottom row OK
            else if (h == height - 1)
            {
                x = -1, y = -1, a = 1, b = 2;
            }
            // free reign
            else if ((h > 0 && w > 0) && (h < height && w < width))
            {
                x = -1, y = -1, a = 2, b = 2;
            }
            else
            {
                break;
            }
            // count average
            for (int i = x; i < a; i++)
            {
                for (int j = y; j < b; j++)
                {
                    goalred = image[h + i][w + j].rgbtRed + goalred;
                    goalgreen = image[h + i][w + j].rgbtGreen + goalgreen;
                    goalblue = image[h + i][w + j].rgbtBlue + goalblue;
                    counter++;
                }
            }

            // counter divider
            temp[h][w].rgbtRed = round(goalred / counter);
            temp[h][w].rgbtGreen = round(goalgreen / counter);
            temp[h][w].rgbtBlue = round(goalblue / counter);

        } // end of w for
    } // end of h for

    // copy over temp values to new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
