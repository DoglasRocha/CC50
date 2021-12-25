#include <stdio.h>
#include <cs50.h>
#include <math.h>

// hints the compiler that these functions are gonna be implemented later
float get_cents(void);
float get_money(void);
int get_number_of_coins(float coin_value, float remaining_value);

// gets the money amound and calculates the minimal amount of coins necessary to change the money
int main(void)
{
    float cents = get_cents();
    float remaining_value = cents;
    int values[4] = {25, 10, 5, 1};
    int number_of_coins;
    int total_coins = 0;

    for (int i = 0; i < 4; i ++)
    {
        int coin = values[i];
        number_of_coins = get_number_of_coins(coin, remaining_value);
        remaining_value -= coin * number_of_coins;
        total_coins += number_of_coins;
    }

    printf("%i\n", total_coins);
}

// by a coin value, calculates the amount of these coin that can "fit" in another value,
// being this value greater than the coin value
int get_number_of_coins(float coin_value, float remaining_value)
{
    int coins = 0;

    while (remaining_value - coin_value >= 0)
    {
        remaining_value -= coin_value;
        coins++;
    }

    return coins;
}

// gets the money amount and multiplies by 100 to get the value in cents
float get_cents(void)
{
    float money = get_money();

    float cents = round(money * 100);

    return cents;
}

// gets the money amount
float get_money(void)
{
    float money = get_float("Troco devido: ");

    if (money > 0)
    {
        return money;
    }

    return get_money();
}