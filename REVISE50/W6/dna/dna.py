import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable
    STR_database = []
    with open(sys.argv[1]) as csv_data:
        reader = csv.DictReader(csv_data)

        for row in reader:
            STR_database.append(row)
    STR_list = list(STR_database[0].keys())
    # CHECK:
    # print(STR_database)
    # print(STR_list)
    # for i in reader:
    #     print(i)

    # Read DNA sequence file into a variable
    sequence_data = open(sys.argv[2], 'r')
    sequence_txt = sequence_data.read()
    # print(sequence_txt)

    # Find longest match of each STR in DNA sequence
    profile = {}
    for seq in range(1, len(STR_list)):
        profile[STR_list[seq]] = longest_match(sequence_txt, STR_list[seq])
    # print(profile)

    # TODO: Check database for matching profiles
    match = "No match"
    for entry in STR_database:
        found = 1
        # print(entry['name'],end=':\n')
        for seq, num in profile.items():
            # print(f"{seq}:",end='')
            # print(f"{entry[seq]} profile:",end='')
            # print(profile[seq],end=' ')
            # remember type imports
            if int(entry[seq]) != int(profile[seq]):
                found = 0
                break
            found = 1
        # if(found == 1):
        if found == 1:
            match = entry['name']
    print(match)
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()


"""
If your program is executed with the incorrect number of command-line arguments, your program should print an error message of your choice
(with print). If the correct number of arguments are provided, you may assume that the first argument is indeed the filename of a valid CSV
 file and that the second argument is the filename of a valid text file.


Your program should open the CSV file and read its contents into memory.
You may assume that the first row of the CSV file will be the column names. The first column will be the word name and the remaining columns will be the STR sequences themselves.

Your program should open the DNA sequence and read its contents into memory.
Sequence is a long string of DNA in text

For each of the STRs (from the first line of the CSV file), your program should compute the longest run of consecutive repeats of the STR in the DNA sequence to identify.Notice that we’ve defined a helper function for you, longest_match, which will do just that!

If the STR counts match exactly with any of the individuals in the CSV file, your program should print out the name of the matching individual.
You may assume that the STR counts will not match more than one individual.
If the STR counts do not match exactly with any of the individuals in the CSV file, your program should print No match

"""