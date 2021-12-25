# include <stdio.h>
# include <stdlib.h>
# include <cs50.h>
# include <math.h>
# include <string.h>

// hints the compiler that these functions are gonna be implemented later
long get_credit_card_number(void);
bool has_valid_length(string number);
bool has_valid_number(string number, int length);
bool check_valid_number(string number, int length, bool even);
bool is_amex(string number);
bool is_master(string number);
bool is_visa(string number);

// get the credit card number and check if it's invalid of if is amex, master or visa
int main(void)
{
    long credit_card_number = get_credit_card_number();
    int length = floor(log10(labs(credit_card_number))) + 1;

    // converting the number to string
    char string_number[length];
    sprintf(string_number, "%li", credit_card_number);

    if (has_valid_length(string_number))
    {
        if (has_valid_number(string_number, length))
        {
            if (is_visa(string_number))
            {
                printf("VISA\n");
            }
            else if (is_master(string_number))
            {
                printf("MASTERCARD\n");
            }
            else if (is_amex(string_number))
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// gets a valid positive long that is the credit card number
long get_credit_card_number(void)
{
    long number = get_long("Número do cartão: ");

    if (number > 0)
    {
        return number;
    }

    return get_credit_card_number();
}

// first validation, checks if the card number is greater than 13
bool has_valid_length(string number)
{
    return (strlen(number) >= 13);
}

// implements the luhn algorithm to check if the card number is valid
bool has_valid_number(string number, int length)
{
    bool even = length % 2 == 0;

    bool is_valid = check_valid_number(number, length, even);
    return is_valid;
}

// hard code luhn algorithm implementation
bool check_valid_number(string number, int length, bool even)
{
    // if the number is even, the caracters to be doubled are the even ones
    // else, the not even ones

    int first_check_value;
    int second_check_value;

    if (even)
    {
        first_check_value = 0;
        second_check_value = 1;
    }
    else
    {
        first_check_value = 1;
        second_check_value = 0;
    }


    int sum = 0;

    // adds the values that need to be double to the sum
    for (int i = length - 1; i > -1; i--)
    {
        if (i % 2 == first_check_value)
        {
            int n = number[i] - '0';
            int doubled_number = n * 2;

            // if the doubled number is greater than 10, it splits the number and add the parts to the sum
            if (doubled_number >= 10)
            {
                char n_greater_than_ten[2];
                sprintf(n_greater_than_ten, "%i", doubled_number);

                for (int h = 0; h < 2; h++)
                {
                    int converted_n = n_greater_than_ten[h] - '0';
                    sum += converted_n;
                }
            }
            else
            {
                sum += doubled_number;
            }
        }
    }

    // adds the values that doesnt need to be doubled to the sum
    for (int j = length - 1; j > -1; j--)
    {
        if (j % 2 == second_check_value)
        {
            int n = number[j] - '0';
            sum += n;
        }
    }

    return (sum % 10 == 0);
}

// checks if the card is amex, which means the number begins with 34 or 37
bool is_amex(string number)
{
    return (number[0] == '3' && (
                number[1] == '4' ||
                number[1] == '7'));
}

// checks if the card is amex, which means the number begins with 51 or 52 or 53 or 54 or 55
bool is_master(string number)
{
    return (number[0] == '5' && (
                number[1] == '1' ||
                number[1] == '2' ||
                number[1] == '3' ||
                number[1] == '4' ||
                number[1] == '5'));
}

// checks if the card is visa, which means the number begins with 4
bool is_visa(string number)
{
    return (number[0] == '4');
}
