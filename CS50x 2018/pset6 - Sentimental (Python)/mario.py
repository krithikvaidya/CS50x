from cs50 import get_int  # importing get_int function


def main():  # main function
    n = get_int("Height: ")  # stores height of the pyramid

    if n > 23 or n < 0:  # checks for invalid input
        main()

    for i in range(n):  # runs once for each row of the pyramid

        for j in range(n - i - 1):  # prints the spaces in the beggining of each row
            print(" ", end="")

        for j in range(i + 1):  # prints the first set of hashes
            print("#", end="")

        print("  ", end="")  # prints the space between the two sets of hashes

        for j in range(i + 1):   # prints the second set of hashes
            print("#", end="")

        print()  # goes to the nextline, so that the next row can be printed


if __name__ == "__main__":  # if the program is interpreted directly, without being imported
    main()