#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // asks the user name and greets the user
    string answer = get_string("What's your name? ");
    printf("Hello, %s!\n", answer);
}