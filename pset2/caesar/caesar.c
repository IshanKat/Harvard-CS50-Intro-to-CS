#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>




int main(int argc, string argv[])
{
    // Check if user has run the program correctly
    if (argc == 2 && argv[1] >= 0)
    {
        // Check if the key is a letter
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]) != 0)
            {
                // Print Usage Message for letter key
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        // Get plaintext and key
        string plaintext = get_string("plaintext: ");
        char ciphertext[100] = {};
        int key = atoi(argv[1]);
        printf("ciphertext: ");
        // Encrypt and print
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            // Checks if char is an alphabet
            if (isalpha(plaintext[i]) != 0)
            {
                // Checks case of letter
                if (isupper(plaintext[i]) == false)
                {
                    plaintext[i] = toupper(plaintext[i]);
                    int converter = (int) plaintext[i] - 65;
                    ciphertext[i] = tolower(((converter + key) % 26) + 65);
                    printf("%c", (char) ciphertext[i]);
                }
                else
                {
                    int converter = (int) plaintext[i] - 65;
                    ciphertext[i] = (((converter + key) % 26) + 65);
                    printf("%c", (char) ciphertext[i]);
                }
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        // Print Usage Message
        printf("Usage: ./caesar key\n");
        return 1;
    }
}