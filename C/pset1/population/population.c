# include <stdio.h>
# include <cs50.h>

// hints the compiler that these functions are gonna be implemented later
int get_initial_population(void);
int get_end_population(int initial_pop);
int calculate_years(int initial_pop, int end_pop);

// gets the initial and end population, calculates the years to reach the end pop
int main(void)
{
    int initial_population = get_initial_population();
    int end_population = get_end_population(initial_population);
    int years = calculate_years(initial_population, end_population);
    printf("Years: %i\n", years);
}

// gets the start population, which has to be greater than 8
int get_initial_population(void)
{
    int population = get_int("Start Size: ");

    if (population < 9)
    {
        return get_initial_population();
    }

    return population;
}

// gets the end population, which has to be equal or greater than the start pop
int get_end_population(int initial_pop)
{
    int end_population = get_int("End size: ");

    if (end_population < initial_pop)
    {
        return get_end_population(initial_pop);
    }

    return end_population;
}

// calculates the amount of years necessary to reach the end population,
// by calculating the births and deaths and summing it up to the
// "current" population
int calculate_years(int initial_pop, int end_pop)
{
    int births;
    int deaths;
    int years = 0;

    for (int p = initial_pop; p < end_pop; p += (births - deaths))
    {
        births = p / 3;
        deaths = p / 4;
        years++;
    }

    return years;
}