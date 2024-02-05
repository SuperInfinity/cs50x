import csv
import sys


def main():

    # TODO: Check for command-line usage
    args = sys.argv
    if len(args) != 3:
        print("Usage: python dna.py f_name.csv f_name.txt")
        return

    # TODO: Read database file into a variable
    database = []
    with open(args[1]) as databases:
        reader = csv.DictReader(databases)
        for row in reader:
            database.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(args[2]) as txt_file:
        dna_seq = txt_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    all_seqs = list(database[0])
    all_seqs.remove("name")
    all_result = []
    for i in range(len(all_seqs)):
        x = longest_match(dna_seq, all_seqs[i])
        all_result.append(x)

    # TODO: Check database for matching profiles
    for rows in database:
        i = 0
        key = 0
        for str in all_seqs:
            if int(rows[str]) == all_result[i]:
                key += 1

            i += 1

        if key == len(all_seqs):
            print(rows["name"])
            return

    print("No match")
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
