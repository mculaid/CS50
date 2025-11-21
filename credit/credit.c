#include <cs50.h>
#include <stdio.h>

string cardCompany = "";

// functions to identify Length and Check card Company
int checkLength(long n);
void checkType(int card, int estimate);

int main(void)
{

    long userNumber = get_long("Number: ");
    // is the length valid, if not, break
    int length = checkLength(userNumber);
    if (length < 13 || length > 16)
    {
        printf("INVALID\n");
        return 0;
    }

    long remainder = userNumber;
    int two, one, sumDoubles, sumFirsts = 0;

    for (int i = 0; i < length; i++)
    {
        if (remainder > 9)
        {
            two = ((remainder % 100) / 10) * 2;
            if (two > 9)
            {
                sumDoubles = sumDoubles + (two / 10) + (two % 10);
            }
            else
            {
                sumDoubles = sumDoubles + two;
            }

            one = remainder % 10;
            sumFirsts = sumFirsts + one;

            if (remainder / 100 > 0)
            {
                remainder = remainder / 100;
            }
            else
            {
                // if card checksum is valid
                if ((sumFirsts + sumDoubles) % 10 == 0)
                {
                    printf("%s\n", cardCompany);
                    return 0;
                }
                // if card is invalid, printf invalid
                else
                {
                    printf("INVALID\n");
                    return 0;
                }
            }
        }
        else if (remainder < 10 && remainder > 0)
        {
            one = remainder % 10;
            sumFirsts = sumFirsts + one;
            remainder = remainder / 10;
            if ((sumFirsts + sumDoubles) % 10 == 0)
            {
                printf("%s\n", cardCompany);
            }
            // if card is invalid, printf invalid
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }
    }
}

int checkLength(long n)
{
    int length = 0;
    while (n > 0)
    {
        if (n / 100 == 0 && n > 9)
        {
            checkType(n, length + 2);
        }

        n = n / 10;
        length++;
    }
    return length;
}

void checkType(int card, int estimate)
{
    if ((card == 51 || card == 52 || card == 53 || card == 54 || card == 55) && estimate == 16)
    {
        cardCompany = "MASTERCARD";
    }
    // check American Express
    else if ((card == 34 || card == 37) && estimate == 15)
    {
        cardCompany = "AMEX";
    }
    // check VISA
    else if ((card / 10 == 4) && (estimate == 13 || estimate == 16))
    {
        cardCompany = "VISA";
    }
    else
    {
        cardCompany = "INVALID";
    }
}
