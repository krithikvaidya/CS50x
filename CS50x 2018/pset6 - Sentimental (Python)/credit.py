from cs50 import get_int  # importing get_int from cs50 library

def main():  # main function
    num = get_int("Number: ")  # getting number from the user
    num3 = num2 = num  # storing copies of the number

    ctr = sum = start = 0

    while num2 > 0:
        if (num2 // 100 == 0) and (num2 // 10 != 0):
            start = start + (num2 % 10)
        elif (num2 // 10 == 0):
            start = start + (num2 % 10) * 10

        ctr = ctr + 1
        num2 = num2 // 10


    if ctr == 13 or ctr == 15 or ctr == 16:
        for i in range(ctr):
            if ((i % 2) == 1):
                prod = (num % 10) * 2

                while prod > 0:
                    sum = sum + (prod % 10)
                    prod = prod // 10

            num = num // 10;

        for i in range(ctr):
            if i % 2 == 0:
                sum = sum + num3 % 10

            num3 = num3 // 10

        if sum % 10 == 0:
            if ctr == 15 and (start == 34 or start == 37):
                print("AMEX")

            elif ((ctr == 16) and (start == 51 or start == 52 or start == 53 or start == 54 or start == 55)):
                print("MASTERCARD")

            elif (ctr == 13 or ctr == 16) and (start // 10 == 4):
                print("VISA")

            else:
                print("INVALID")

        else:
            print("INVALID")

    else:
        print("INVALID")


if __name__ == "__main__":
    main()