/*
CS50PS1 Mario More Comfortable
code_tofu
*/

#include <stdio.h>
#include <cs50.h>


int main()
{
    int height = 0, i = 0, j = 0;

    while (height < 1 || height > 8)
    {
        height = get_int("Height:");
    }

    for (i = 1; i <= height; i++)
    {
        for (j = (height - i); j > 0; j--)
        {
            printf(" ");
        }
        for (j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (j = 0; j < i ; j++)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}

/*
User gives an input to decide just how tall the pyramid should be, and programme ouputs a mario pyramid

Input:
positive integer between 1 and 8 inclusive.

$ ./mario
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
*/