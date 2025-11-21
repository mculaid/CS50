import csv
from sys import argv


def main():

    # TODO: Check for command-line usage
    if len(argv) < 3:
        print("Usage: dna.py db.csv seq.csv")
        exit()

    dbValues = []

    # TODO: Read database file into a variable
    with open(argv[1], newline='') as file:
        fp_db = csv.DictReader(file)
        for row in fp_db:
            dbValues.append((row))

    # TODO: Read DNA sequence file into a variable
    f = open(argv[2], "r")
    dnaseq = f.read()

    # TODO: Find longest match of each STR in DNA sequence
    winner = False
    winnerName = ""
    for person in dbValues:
        amount = 0
        for key in person.keys():
            if key != "name":

                # TODO: Check database for matching profiles
                if int(person[key]) == longest_match(dnaseq, key):
                    amount += 1
                    if amount == len(person) - 1:
                        # print(person['name'])
                        winnerName = person['name']
                        winner = True
                        break

    # Do we have a winner?
    if winner == False:
        print("No match")
    else:
        print(winnerName)


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
