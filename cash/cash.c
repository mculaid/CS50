#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int cash = -1;
    int counter = 0;

    // Loop for input
    while (cash <= 0)
    {
        cash = get_int("Change owed: ");
    }
    while (cash > 0)
    {
        if (cash - 25 >= 0)
        {
            cash = cash - 25;
            counter++;
        }
        else if (cash - 10 >= 0)
        {
            cash = cash - 10;
            counter++;
        }
        else if (cash - 5 >= 0)
        {
            cash = cash - 5;
            counter++;
        }
        else if (cash - 1 >= 0)
        {
            cash = cash - 1;
            counter++;
        }
    }
    printf("%i\n", counter);
}
