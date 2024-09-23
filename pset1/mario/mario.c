#include <stdio.h>
#include <cs50.h>

void pyramid(void);

int main(void)
{
    pyramid();
}










void pyramid(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    int hash = 1;
    int space = n - hash;

    for (int i = 0; i < n; i++)
    {
        // First spaces
        for (int j = 0; j < space; j++)
        {
            printf(" ");
        }
        // First hashes
        for (int j = 0; j < hash; j++)
        {
            printf("#");
        }
        // Space in the middle
        for (int j = 0; j < 2; j++)
        {
            printf(" ");
        }
        // Second hashes
        for (int j = 0; j < hash; j++)
        {
            printf("#");
        }
        // Changing amount of space
        space -= 1;
        hash = n - space;

        // New row
        printf("\n");
    }

}