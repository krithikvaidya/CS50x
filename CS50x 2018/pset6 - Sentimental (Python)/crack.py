import sys  # for command-line arguments
import crypt  # for crypt.crypt() function


def main():  # main function

    if len(sys.argv) != 2:  # checks if the user correctly runs the program
        print("Usage: python crack.py hash")
        sys.exit(1)  # invalid usage format, exits with code 1

    key = sys.argv[1]  # the hashed password
    salt = sys.argv[1][0] + sys.argv[1][1]  # salt, the first two characters of the hashed password

    letter_range = 53  # a constant

    # storing all possible letters that can be present in a password
    # whitespace denotes that no character is present at that position
    letters = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

    finalPass = ['', '', '', '', '']  # finalPass stores each possible password for checking
    finalStr = ''  # stores finalPass in a string instead of a list

    for i in range(letter_range):  # sets the value of the last character of finalPass
        finalPass[4] = letters[i]

        for j in range(letter_range):  # sets the value of the 4th character of finalPass
            finalPass[3] = letters[j]

            for k in range(letter_range):  # sets the value of 3rd character of finalPass
                finalPass[2] = letters[k]

                for l in range(letter_range):  # sets the value of 2nd character of finalPass
                    finalPass[1] = letters[l]

                    for m in range(letter_range):  # sets the value of first character of finalPass
                        finalPass[0] = letters[m]

                        # now, hash of each possible password is checked, and
                        # if this generated hash is equal to the hash entered
                        # by the user, finalStr is the required password.

                        finalStr = ''.join(finalPass)
                        if crypt.crypt(finalStr.strip(), salt) == sys.argv[1]:
                            print(finalStr)
                            sys.exit(0)  # password found, exit with code 0

    sys.exit(2)  # password not found, exit with code 2


if __name__ == "__main__":  # calls main() function if the program is interpreted directly(i.e. without importing)
    main()