#include <stdio.h>
#include <cs50.h>
//this is the main function
int main(void)
{
    //this prompts the user for their name
    string name = get_string("What's your name? ");
    //this greets the user by saying "hello" using their name
    printf("hello, %s\n", name);
}