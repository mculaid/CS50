from cs50 import get_float


def main():
    try:
        amountGiven = get_float("Change: ")
        if (amountGiven > 0):
            # multiply to get away from float
            count(amountGiven * 100)
        else:
            main()
    # catch non-float input
    except ValueError:
        print(main())


def count(amount):

    # initialize coin-amount and values per coin
    a = 0
    coins = [25, 10, 5, 1]

    # run this loop until running out of change
    while amount > 0:
        for coin in coins:
            if amount - coin >= 0:
                amount -= coin
                a += 1
                break

    print(int(a))


main()
