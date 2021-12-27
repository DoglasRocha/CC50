#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// hints the compiler that these functions are gonna be implemented later
int throw_incorrect_usage(void);
int throw_incorrect_letter_amount(void);
int throw_incorrect_character(void);
int throw_duplicate(void);
int throw_message_and_return_1(string message);
void cipher_text(string base_text, string cipher);
string validate_cipher(string cipher);

int main(int argc, string argv[])
{
    // checks if the args count is equal to 2, if not, throws error
    if (argc == 2)
    {
        // validates the cipher
        string cipher = validate_cipher(argv[1]);

        if (strcmp(cipher, "amount") == 0)
        {
            return throw_incorrect_letter_amount();
        }
        else if (strcmp(cipher, "character") == 0)
        {
            return throw_incorrect_character();
        }
        else if (strcmp(cipher, "duplicate") == 0)
        {
            return throw_duplicate();
        }

        // gets the base text and ciphers it
        string base_text = get_string("base text: ");
        cipher_text(base_text, cipher);

        return 0;

    }

    return throw_incorrect_usage();
}

int throw_incorrect_letter_amount(void)
{
    return throw_message_and_return_1(
               "The key must contain 26 characters\n");
}

int throw_incorrect_usage(void)
{
    return throw_message_and_return_1(
               "Usage: ./substitution key\n");
}

int throw_incorrect_character(void)
{
    return throw_message_and_return_1(
               "The key must contain only alphabetic characters\n");
}

int throw_duplicate(void)
{
    return throw_message_and_return_1(
               "The key must not have duplicates\n");
}

// generic error message
int throw_message_and_return_1(string message)
{
    printf("%s", message);
    return 1;
}


void cipher_text(string base_text, string cipher)
{
    
    string cipher_text = base_text;

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphabet_length = strlen(alphabet);

    // for every letter of the base text, checks if is lower, then 
    // checks if is an alphabetic character, then gets its position
    // in the normal alphabet to put it in the correct cipher
    
    // if the base character is lower, then the cipher is lower,
    // otherwise, the cipher is upper 
    for (int i = 0, n = strlen(base_text); i < n; i++)
    {
        char letter = base_text[i];
        bool is_lower = islower(base_text[i]);

        if (isalpha(letter))
        {
            for (int j = 0; j < alphabet_length; j++)
            {
                if (toupper(letter) == alphabet[j])
                {
                    if (is_lower)
                    {
                        cipher_text[i] = tolower(cipher[j]);
                    }
                    else
                    {
                        cipher_text[i] = toupper(cipher[j]);
                    }

                    break;
                }
            }
        }
    }
    
    // prints the cipher
    printf("ciphertext: %s\n", cipher_text);
}


// validates the cipher 

// first: checks if its length is equal to 26, if not, return message
// second: checks if every character is alphabetic, if not, return message
// third: checks if the cipher has duplicates, if has, return message
// fourth: if all the previous requirements are matched, return the cipher 

string validate_cipher(string cipher)
{
    if (strlen(cipher) == 26)
    {
        for (int i = 0; i < 26; i++)
        {
            if (isalpha(cipher[i]))
            {
                for (int j = 0; j < i; j++)
                {
                    if (cipher[i] == cipher[j])
                    {
                        return "duplicate";
                    }
                }
            }
            else
            {
                return "character";
            }

        }

        return cipher;
    }

    return "amount";
}