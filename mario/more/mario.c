#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // initialize height and prompt
    int height = 0;
    while (height > 8 | height < 1)
    {
        height = get_int("What is the height?");
    }
    int counter = 0;
    while (counter < height)
    {
        for (int i = counter + 1; i < height; i++)
        {
            printf(" ");
        }
        for (int j = 0; j <= counter; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 0; k <= counter; k++)
        {
            printf("#");
        }
        printf("\n");
        counter++;
    }
}
