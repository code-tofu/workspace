import cs50


def main():
    input_sentence = cs50.get_string("Text:")
    letters = count_letters(input_sentence)
    words = count_words(input_sentence)
    sentences = count_sentence(input_sentence)
    # print(f"{letters} letters")
    # print(f"{words} words")
    # print(f"{sentences} sentences")
    index = round(0.0588 * (letters/words*100) - 0.296 * (sentences/words*100) - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")

def count_words(sentence):
    # to account for last word, which will not have a space
    words = 1
    for i in sentence:
        if (i == ' '):
            words += 1
    return words


def count_letters(sentence):
    letters = 0
    for character in sentence:
        if(character.isalpha()):
            letters += 1
    return letters


def count_sentence(sentence):
    sentence_end = ".!?"
    sentences = 0
    for character in sentence:
        if(character in sentence_end):
            sentences += 1
    return sentences


main()


"""
The Coleman-Liau index of a text is designed to output that (U.S.) grade level that is needed to understand some text.
The formula is index = 0.0588 * L - 0.296 * S - 15.8
where L is the average number of letters per 100 words in the text,
and S is the average number of sentences per 100 words in the text.

You may assume that a sentence:
will contain at least one word;
will not start or end with a space; and
will not have multiple spaces in a row.
Consider letters to be uppercase or lowercase alphabetical character, not punctuation, digits, or other symbols.
Consider any sequence of characters that ends with a . or a ! or a ? to be a sentence
But of course, not all periods necessarily mean the sentence is over.
For this problem, we’ll ask you to ignore that subtlety

"""