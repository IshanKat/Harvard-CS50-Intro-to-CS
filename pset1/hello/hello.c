#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Question
    string answer = get_string("What's your name?\n");
    // Greeting
    printf("Hello, %s.\n", answer);
}