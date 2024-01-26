#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

int only_digits(string userinput);
int atoi(string s);
char rotate(char userTextChar, int userKey);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (!(only_digits(argv[1])))
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }

    int userKey = atoi(argv[1]);
    // printf("key:%d\n", userKey);

    string userString = get_string("plaintext: ");

    printf("ciphertext:");
    int i = 0;
    while (userString[i] != '\0')
    {
        printf("%c", rotate(userString[i], userKey));
        i++;
    }
    printf("\n");
    return 0;
}


int only_digits(string userInput)
{
    int i = 0;
    while (userInput[i] != '\0')
    {
        if (userInput[i] < 48 || userInput[i] > 57)
        {
            return false;
        }
        i++;
    }
    return true;
}

char rotate(char userTextChar, int userKey)
{
    int shift = (userKey % 26);
    if ((userTextChar > 96 && userTextChar < 123))
    {
        if ((userTextChar + shift) < 123)
        {
            userTextChar = userTextChar + shift; //assume non-negative
        }
        else
        {
            userTextChar = 96 + (userTextChar + shift - 122); //wrap around z
        }
    }
    if ((userTextChar > 64 && userTextChar < 91))
    {
        if ((userTextChar + shift) < 91)
        {
            userTextChar = userTextChar + shift; //assume non-negative
        }
        else
        {
            userTextChar = 64 + (userTextChar + shift - 90); //wrap around z
        }
    }
    return userTextChar;
}


/*
Implement your program in a file called caesar.c in a directory called caesar.
Your program must accept a single command-line argument, a non-negative integer. Let’s call it k for the sake of discussion.
If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.
If any of the characters of the command-line argument is not a decimal digit, your program should print the message Usage: ./caesar key and return from main a value of 1.
Do not assume that  will be less than or equal to 26. Your program should work for all non-negative integral values of k less than 2^31-26. In other words, you don’t need to worry if your program eventually breaks if the user chooses a value for  that’s too big or almost too big to fit in an int. (Recall that an int can overflow.) But, even if  is greater than , alphabetical characters in your program’s input should remain alphabetical characters in your program’s output. For instance, if k is 27, A should not become \ even though \ is  positions away from A in ASCII, per asciichart.com; A should become B, since B is 27 positions away from A, provided you wrap around from Z to A.
Your program must output plaintext: (with two spaces but without a newline) and then prompt the user for a string of plaintext (using get_string).
Your program must output ciphertext: (with one space but without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext “rotated” by k positions; non-alphabetical characters should be outputted unchanged.
Your program must preserve case: capitalized letters, though rotated, must remain capitalized letters; lowercase letters, though rotated, must remain lowercase letters.
After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.

modify main in caesar.c in such a way that, if the user provides no command-line arguments, or two or more, the function prints "Usage: ./caesar key\n" and then returns 1, effectively exiting the program. If the user provides exactly one command-line argument, the program should print nothing and simply return 0.
Add to caesar.c, below main, a function called, e.g., only_digits that takes a string as an argument and returns true if that string contains only digits, 0 through 9, else it returns false. Then modify main in such a way that it calls only_digits on argv[1]. If that function returns false, then main should print "Usage: ./caesar key\n" and return 1. Else main should simply return 0.

Now modify main in such a way that it converts argv[1] to an int. You might find atoi, declared in stdlib.h, to be helpful, per manual.cs50.io. And then use get_string to prompt the user for some plaintext with "plaintext: ".

Then, implement a function called, e.g., rotate, that takes a char as input and also an int, and rotates that char by that many positions if it’s a letter (i.e., alphabetical), wrapping around from Z to A (and from z to a) as needed. If the char is not a letter, the function should instead return the same char unchanged.

Then modify main in such a way that it prints "ciphertext: " and then iterates over every char in the user’s plaintext, calling rotate on each, and printing the return value thereof.


*/