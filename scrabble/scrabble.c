#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int LETTERS = 26;

int pointsFunction(string word, int arrayLetters[], int arrayPoints[], int points);

int main(void)
{
    int charPoints[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int charLetters[LETTERS];

    string wordA = get_string("Player 1: ");
    string wordB = get_string("Player 2: ");

    // initialize alphabetic array
    int counter = 65;
    for (int i = 0; i < LETTERS; i++)
    {
        charLetters[i] = counter;
        counter++;
    }

    // call function
    int pointsPlayerA = 0;
    int pointsPlayerB = 0;
    if (pointsFunction(wordA, charLetters, charPoints, pointsPlayerA) >
        pointsFunction(wordB, charLetters, charPoints, pointsPlayerB))
    {
        printf("Player 1 wins!\n");
    }
    else if (pointsFunction(wordA, charLetters, charPoints, pointsPlayerA) <
             pointsFunction(wordB, charLetters, charPoints, pointsPlayerB))
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int pointsFunction(string word, int arrayLetters[], int arrayPoints[], int points)
{
    points = 0;
    // iterate over word - should be a function
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (toupper(word[i]) >= 65 && toupper(word[i]) <= 90)
        {
            // iterate over array of alphabet to find position of letter
            for (int j = 0; j < LETTERS; j++)
            {
                if (arrayLetters[j] == toupper(word[i]))
                {
                    points = points + arrayPoints[j];
                }
            }
        }
    }
    return points;
}
