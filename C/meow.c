# include <stdio.h>

// prototype, it indicates the compiler that a function with this name is
// gonna be declared
void meow(int count);

int main(void)
{
    meow(9);
}

void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}