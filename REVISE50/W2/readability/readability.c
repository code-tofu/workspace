/*
CS50 Readability
code_tofu
*/

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{

    string userstr = get_string("Text:");
    // printf("%d letters\n",count_letters(userstr));
    // printf("%d words\n",count_words(userstr));
    // printf("%d sentences\n",count_sentences(userstr));

    int words = count_words(userstr);
    int index = round((0.0588 * ((float)count_letters(userstr) / (float)words * 100.00)) - (0.296 * ((float)count_sentences(userstr) /
                      (float)words) * 100.00) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
    return 0;
}

int count_letters(string text)
{
    int i = 0, count = 0;
    while (text[i] != '\0') //note comparison to char, not string
    {
        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123))
        {
            count++;
        }
        i++;
    }
    return count;
}


int count_words(string text)
{
    int i = 0, count = 1; //count from 1 to include last word
    while (text[i] != '\0')
    {
        if (text[i] == 32)
        {
            count++;
        }
        i++;
    }
    return count;
}

int count_sentences(string text)
{
    int i = 0, count = 0; //count from 1 to include last word
    while (text[i] != '\0')
    {
        if ((text[i] == '.') || (text[i] == '?') || (text[i] == '!'))
        {
            count++;
        }
        i++;
    }
    return count;
}

/*
Implement in readability.c a main function that prompts the user with "Text: " using get_string and then prints that same text using printf
a function called count_letters that takes one argument, a string of text, and that returns an int, the number of letters in that text
Consider letters to be uppercase or lowercase alphabetical character, not punctuation, digits, or other symbols.


Add to readability.c, below main, a function called count_words that takes one argument, a string of text, and that returns an int, the number of words in that text.
Then call that function in main so that your program also prints the number of words in the text.
You may assume that a sentence:
will contain at least one word;
will not start or end with a space; and
will not have multiple spaces in a row.
You are, of course, welcome to attempt a solution that will tolerate multiple spaces between words or indeed, no words!

You might first imagine that a sentence is just any sequence of characters that ends with a period, but of course sentences could end with an exclamation point or a question mark as well. But of course, not all periods necessarily mean the sentence is over.
This is just a single sentence, but there are three periods! For this problem, we’ll ask you to ignore that subtlety: you should consider any sequence of characters that ends with a . or a ! or a ? to be a sentence (so for the above “sentence”, you should count it as three sentences). In practice, sentence boundary detection needs to be a little more intelligent to handle these cases, but we’ll not worry about that for now.
Add a function called count_sentences that takes one argument, a string of text, and that returns an int, the number of sentences in that text.

 the Coleman-Liau index is computed using the formula:
index = 0.0588 * L - 0.296 * S - 15.8
where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
L = Letters ÷ Words × 100
S = Sentences ÷ Words × 100

Modify main in readability.c to output (only) the grade level as defined by the Coleman-Liau index (e.g. "Grade 2" or "Grade 8" or the like). Be sure to round the resulting index number to the nearest int!

*/