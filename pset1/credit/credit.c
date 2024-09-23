#include <stdio.h>
#include <cs50.h>

void validate(void);

int main(void)
{
    validate();
}





void validate(void)
{
    long number = get_long("Number: ");
    // Digits go from right to left
    int digits = 0;
    int digit_list[50] = {};
    int digit_place = 0;
    int multiplied_digits[50] = {};
    int leftover_digits[50] = {};
    int multiplier = 1;
    long get_digits = number;
    while (get_digits != 0)
    {
        digit_list[digit_place] = get_digits % 10;
        get_digits = (get_digits - digit_list[digit_place]) / 10;
        digit_place += 1;
        digits += 1;
    }
    digit_place = 0;
    // Getting the digits of the number
    while (multiplier <= digits)
    {
        multiplied_digits[digit_place] = digit_list[multiplier] * 2;
        if (multiplied_digits[digit_place] >= 10)
        {
            multiplied_digits[digit_place] = multiplied_digits[digit_place] % 10;
            digit_place += 1;
            multiplied_digits[digit_place] = 1;
        }
        digit_place += 1;
        multiplier += 2;
    }
    multiplier = 0;
    int checksum_part1 = 0;
    while (multiplier < digit_place)
    {
        checksum_part1 += multiplied_digits[multiplier];
        multiplier += 1;
    }
    multiplier = 0;
    digit_place = 0;
    while (multiplier <= digits)
    {
        leftover_digits[digit_place] = digit_list[multiplier];
        digit_place += 1;
        multiplier += 2;
    }
    multiplier = 0;
    int checksum_part2 = 0;
    while (multiplier < digit_place)
    {
        checksum_part2 += leftover_digits[multiplier];
        multiplier += 1;
    }
    int checksum = checksum_part1 + checksum_part2;
    // Identification
    if (checksum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (digits <= 13)
    {
        printf("INVALID\n");
    }
    else if (digit_list[digits - 1] == 4)
    {
        if (digits == 13 || digits == 16)
        {
            printf("VISA\n");
        }
    }
    else if (digit_list[digits - 1] == 3)
    {
        if (digit_list[digits - 2] == 4 || digit_list [digits - 2] == 7)
        {
            if (digits == 15)
            {
                printf("AMEX\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (digit_list[digits - 1] == 5)
    {
        if (digit_list[digits - 2] == 1 || digit_list[digits - 2] == 2
        || digit_list[digits - 2] == 3 || digit_list[digits - 2] == 4
        || digit_list[digits - 2] == 5)
        {
            if (digits == 16)
            {
                printf("MASTERCARD\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("OTHER\n");
    }

}