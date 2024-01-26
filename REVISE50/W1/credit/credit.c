/*
CS50 PS1 Credit
code_tofu
*/

#include <cs50.h>//contains get_long prototype
#include <stdio.h>
#include <math.h>

int get_length(long cardNum);
int check_sum(long cardNum, int numDigits);

int main(void)
{
    //Prompt for number. Get long rejects non-numeric input and repeats query
    long cardNum = get_long("Number:");

    //determine credit card length
    int numDigits = get_length(cardNum);
    // printf("%d",numDigits);

    if (numDigits == 0)
    {
        printf("INVALID\n");
        return 0;
    }

    int checkSumValid = check_sum(cardNum, numDigits);
    if (checkSumValid == 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // printf("VALID\n");

    //check for AMEX
    if (
        (numDigits == 15) &&
        (((int)(cardNum / pow(10, 13)) == 37) ||
         ((int)(cardNum / pow(10, 13)) == 34))
    )
    {
        printf("AMEX\n");
        return 0;
    }

    //Check for VISA
    if (
        ((numDigits == 13) || (numDigits == 16)) &&
        (((int)(cardNum / pow(10, 15)) == 4) ||
         ((int)(cardNum / pow(10, 12)) == 4))
    )
    {
        printf("VISA\n");
        return 0;
    }

    //Check for MASTER
    if (
        (numDigits == 16) &&
        (((int)(cardNum / pow(10, 14)) == 51) ||
         ((int)(cardNum / pow(10, 14)) == 52) ||
         ((int)(cardNum / pow(10, 14)) == 53) ||
         ((int)(cardNum / pow(10, 14)) == 54) ||
         ((int)(cardNum / pow(10, 14)) == 55))
    )
    {
        printf("MASTERCARD\n");
        return 0;
    }

    //fall through case for number checks
    printf("INVALID\n");

    return 0;
}


// RETURNS LENGTH OF CARD NUMBER
int get_length(long cardNum)
{
    //returns 0 if less than 13 numbers or more than 16 numbers
    if (((cardNum / pow(10, 12)) <= 1) || ((cardNum / pow(10, 16)) >= 1))
    {
        return 0;
    }

    if ((cardNum / pow(10, 15)) > 1)
    {
        return 16;
    }
    else if ((cardNum / pow(10, 14)) > 1)
    {
        return 15;
    }
    else if ((cardNum / pow(10, 13)) < 1)
    {
        return 13;
    }
    else
    {
        return 0;
    }

}

// CHECKS IF CARD IS VALID
int check_sum(long cardNum, int numDigits)
{
    int sum = 0, digit = 0;
    long tens = 0;

    int i = 1;
    //first operation
    while (i < numDigits)
    {
        //get digit and product of digit*2
        tens = (cardNum / pow(10, (i)));
        digit = (tens % 10) * 2;
        //get digits of product and sum
        sum += (digit / 10) + (digit % 10);
        i += 2;
    }

    //second operation
    i = 0;
    while (i < numDigits)
    {
        tens = (cardNum / pow(10, (i)));
        digit = (tens % 10);
        i += 2;
        sum += digit;
    }

    //return value
    if (sum % 10 != 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*
Write a program that prompts the user for a credit card number and then reports (via printf) whether it is a valid American Express, MasterCard, or Visa card number, per the definitions of each’s format herein:
All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55 and all Visa numbers start with 4.
American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers

So that we can automate some tests of your code, we ask that your program’s last line of output be AMEX\n or MASTERCARD\n or VISA\n or INVALID\n
For simplicity, you may assume that the user’s input will be entirely numeric (i.e., devoid of hyphens, as might be printed on an actual card) and that it won’t have leading zeroes.
But do not assume that the user’s input will fit in an int! Best to use get_long from CS50’s library to get users’ input. (Why?)

Luhn’s Algorithm:
Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
Add the sum to the sum of the digits that weren’t multiplied by 2.
If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

https://developer.paypal.com/api/nvp-soap/payflow/integration-guide/test-transactions/#standard-test-cards


//better code for get_length
int i = 0;
long cNum = cardNum;
while (cNum  > 0)
{
    cNum  = cNum / 10;
    i++;
}

*/