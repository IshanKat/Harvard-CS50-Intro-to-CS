#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Getting User Input
    string input = get_string("Text: ");
    // Declaring Variables
    double letters = 0;
    double words = 0;
    double sentences = 0;
    double multiplier;
    float grade;
    // Finding the Amount of Words/Letters/Sentences
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if ((input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123))
        {
            letters++;
        }
        else if (input[i] == 32)
        {
            words++;
        }
        else if (input[i] == 46 || input[i] == 33 || input[i] == 63)
        {
            sentences++;
        }

    }
    // Add one word for the last word without a space after it
    if (words != 0)
    {
        words++;
    }
    // Set up proportions
    multiplier = 100 / words;
    words *= multiplier;
    letters *= multiplier;
    sentences *= multiplier;
    // Implement Coleman-Liau Index
    grade = round(0.0588 * letters - 0.296 * sentences - 15.8);
    //Print Grade Level
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) grade);
    }
}