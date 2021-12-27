#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// hints the compiler that these functions are gonna be implemented later
string get_text_from_user(void);
void cipher_text(string text, int number);
int throw_incorrect_usage(void);


int main(int argc, string argv[])
{
    // if the number os args is greater equal to 2, keeps the program running
    if (argc == 2)
    {
        // verifies if all the characters if the arg are positive numbers
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                return throw_incorrect_usage();
            }
        }

        // convert the number to a int and discover the "true number"
        // (in case of it is greater than 26)
        int number = atoi(argv[1]);
        number %= 26;

        // if the number is 0, it means that a incorrect key was given,
        // so, the program refuses it
        if (number > 0)
        {
            string text = get_text_from_user();
            cipher_text(text, number);

            return 0;
        }
        
        // prints error message and returns 1
        return throw_incorrect_usage();
    }
    // prints error message and returns 1
    return throw_incorrect_usage();
}

// gets the text from the user
string get_text_from_user(void)
{
    string text = get_string("plaintext: ");

    return text;
}

// aplies the cipher to the text and prints it
void cipher_text(string text, int number)
{
    int text_length = strlen(text);
    char cipher[text_length];

    for (int i = 0; i < text_length; i++)
    {
        char character = text[i];

        if (character != ' ' && !ispunct(character))
        {
            int code = (int)text[i] + number;

            // if the unicode is in the "valid gap", just define the character
            // else, remove 26 of it (the number to make it go the beggining)
            if ((code >= 65 && code <= 90)
                || (code >= 97 && code <= 122))
            {
                character = text[i] + number;
            }
            else
            {
                character = text[i] + number - 26;
            }
        }

        cipher[i] = character;
    }

    printf("ciphertext: %s\n", cipher);

}

int throw_incorrect_usage(void)
{
    printf("Usage: ./caesar key\n");
    return 1;
}