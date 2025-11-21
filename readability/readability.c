#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text:\n");

    int letters = 0;
    int words = 0;
    int sentences = 0;
    int wordsInASentence = 0;
    float indexT = 0;
    float indexL = 0;
    float indexS = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // is char a letter
        if (isalpha(text[i]) != 0)
        {
            letters++;
        }
        // is this a space
        else if (text[i] == 32)
        {
            if (text[i - 1] != 33 && text[i - 1] != 63 && text[i - 1] != 46)
            {
                words++;
            }
        }
        // is this . ? !
        else if (text[i] == 33 || text[i] == 63 || text[i] == 46)
        {
            sentences++;
            words++;
        }
    }
    indexL = (letters / (float) words) * 100.0;
    indexS = (sentences / (float) words) * 100.0;

    indexT = 0.0588 * indexL - 0.296 * indexS - 15.8;

    if (indexT < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (indexT > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(indexT));
    }
}
