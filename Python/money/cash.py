# gets a user input of a change value and return the amount of coins needed for
# that change
def main() -> None:
    money = get_money()

    coins_available = [.25, .1, .05, .01]

    given_coins = calc_coins_given(money, coins_available, 0)

    print(int(given_coins))


# gets the money
# rejects every input except a positive float
def get_money() -> float:

    str_money = input('Change owed: ')

    try:
        money = float(str_money)

        if (money > 0):
            return money

        return get_money()

    except:
        return get_money()


# recursively, calculates the coins that are needed to change the value
# first, calculate the coins for a given value, calculate the rest of the division
# then, test base case, then activates the recursion, passing the rest 
# to the function and summing up with the previous value of coins
# then, return the all the coins
def calc_coins_given(money: float, coins_available: list,
                     position: int) -> int:
    coins = money // coins_available[position]
    remaining_money = round(money % coins_available[position], 2)

    if (remaining_money != 0):
        coins += calc_coins_given(remaining_money, coins_available,
                                  position + 1)

    return coins


main()