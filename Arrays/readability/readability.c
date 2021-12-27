#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

// hints the compiler that these functions are gonna be implemented later
string get_text(void);
int calculate_grade(int letters, int words, int sentences);

int main(void)
{
    // declare variables
    string text = get_text();
    int letters = 0;
    // words declared with 1 because otherwise one word will not be counted,
    // due to its count depend on the space character
    int words = 1;
    int sentences = 0;

    // check every character
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // if the character is alphabetic, increase letter variable
        if (isalpha(text[i]))
        {
            letters++;
        }
        // if the character is a space (or something like), increase words variable
        else if (isspace(text[i]))
        {
            words++;
        }
        // if the character is a punctuation, increase sentences variable
        else if (ispunct(text[i])
                 && (text[i] == '.'
                     || text[i] == '!'
                     || text[i] == '?'))
        {
            sentences++;
        }
    }

    // calculates the grade
    int grade = calculate_grade(letters, words, sentences);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 1 && grade <= 16)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Grade 16+\n");
    }

    return 0;
}

// gets the text from the user
string get_text(void)
{
    string text = get_string("Text: ");

    return text;
}

// calculates the grade according to the number of letters, words and sentences
int calculate_grade(int letters, int words, int sentences)
{
    float hundred_words = words / 100.0;
    float l = letters / hundred_words;
    float s = sentences / hundred_words;

    float grade = 0.0588 * l - 0.296 * s - 15.8;

    return round(grade);
}
