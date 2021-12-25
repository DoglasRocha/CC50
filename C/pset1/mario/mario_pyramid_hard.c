# include <stdio.h>
# include <cs50.h>

// functions that are gonna be implemented later
int get_positive_number(void);
bool is_equal_or_less_than_eight(int number);
int get_size(void);

// builds the pyramid
int main(void)
{
    int size = get_size();

    for (int i = 0; i < size; i++)
    {
        int spaces = size - 1 - i;

        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }
        
        for (int l = 0; l < 2; l++)
        {
            for (int k = size; k > spaces; k--)
            {
                printf("#");
            }
            
            if (l == 0)
            {
                for (int s = 0; s < 2; s++)
                {
                    printf(" ");
                }
            }
        }

        printf("\n");
    }
}

// get a positive number from the user using recursive function
int get_positive_number(void)
{
    int n = get_int("Size: ");

    if (n > 0)
    {
        return n;
    }

    return get_positive_number();
}

// verifying if the number is >= 8
bool is_equal_or_less_than_eight(int number)
{
    return (number <= 8);
}

// gets the size of the pyramid
int get_size(void)
{
    int number = get_positive_number();

    if (is_equal_or_less_than_eight(number))
    {
        return number;
    }

    return get_size();
}