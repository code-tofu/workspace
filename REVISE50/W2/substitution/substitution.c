#include <cs50.h>
#include <stdio.h>
const string refKey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int checkAlphaKey(string userKey, int keyArray[26]);
void substitute(string userString, int keyArray[26]);
int main(int argc, string argv[])
{

    //check 2 argument inputs
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //check validity of input key and create key array
    int keyArray[26] = {0};
    int validKey = checkAlphaKey(argv[1], keyArray);
    if (validKey)
    {
        printf("Key must contain 26 alphabetic characters.\n");
        return 1;
    }
    string userString = get_string("plaintext: ");
    substitute(userString, keyArray);
    printf("ciphertext: %s\n", userString);
    return 0;
}

int checkAlphaKey(string userKey, int keyArray[26]) //returns 1 if invalid.
{
    int len = 0;
    //check key length is 26;
    while (userKey[len] != '\0')
    {
        len++;
    }
    if (len != 26)
    {
        return 1;
    }

    char userKeyReference[26] = {0};
    int i = 0;
    while (userKey[i] != '\0')
    {
        // check for alpha
        if (!((userKey[i] >= 'a' && userKey[i] <= 'z') || (userKey[i] >= 'A' && userKey[i] <= 'Z'))) //use char instead of ASCII value
        {
            return 1;
        }
        userKeyReference[i] = userKey[i];
        //CHECK: printf("\n%c>%c", userKey[i],userKeyReference[i]);
        // check for repeated
        for (int j = 0; j < i; j++) //you can declare j in brackets?
        {
            if (userKey[i] == userKeyReference[j])
            {
                return 1;
            }
            //CHECK: printf("check:%c", userKeyReference[j]);
        }
        if ((userKey[i] > 96 && userKey[i] < 123)) //convert all to upper for key Array
        {
            keyArray[i] = userKey[i] - 32;
        }
        else
        {
            keyArray[i] = userKey[i];
        }

        i++;
    }
    return 0;
}

void substitute(string userString, int keyArray[26])
{
    int i = 0;
    while (userString[i] != '\0')
    {
        if (((userString[i] > 64 && userString[i] < 91))) //Character is Alpha Uppercase
        {

            for (int j = 0; j < 26 ; j++)
                if (userString[i] == refKey[j])
                {
                    userString[i] = keyArray[j];
                    break;
                }
        }

        if (((userString[i] > 96 && userString[i] < 123))) //Character is Alpha Lowercase
        {
            for (int j = 0; j < 26 ; j++)
                if ((userString[i] - 32) == refKey[j])
                {
                    userString[i] = keyArray[j] + 32;
                    break;
                }
        }
        i++;
    }
}


/*
Design and implement a program, substitution, that encrypts messages using a substitution cipher.
Implement your program in a file called substitution.c in a directory called substitution.
Your program must accept a single command-line argument, the key to use for the substitution. The key itself should be case-insensitive, so whether any character in the key is uppercase or lowercase should not affect the behavior of your program.
If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.
If the key is invalid (as by not containing 26 characters, containing any character that is not an alphabetic character, or not containing each letter exactly once), your program should print an error message of your choice (with printf) and return from main a value of 1 immediately.
>> uppercase all (use toupper?) and sum to unique sum of 26 letters = 2015?
Your program must output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext; non-alphabetical characters should be outputted unchanged.
Your program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.
After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.


a = 97 - z = 122
A = 65 - Z = 90
*/