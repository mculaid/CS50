#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Input
    int input = 0;
    while (input < 1 || input > 8)
    {

        input = get_int("Input a number between 1 and 8\n");
    }

    int height = input;
    int counter = 1;

    // Loop printf("");
    while (height > 0)
    {

        // print Spaces
        for (int spaces = height - 1; 0 < spaces; spaces--)
        {
            printf(" ");
        }

        // print Blocks
        for (int blocks = 0; blocks < counter; blocks++)
        {
            printf("#");
        }

        counter++;
        height -= 1;
        printf("\n");
    }

}