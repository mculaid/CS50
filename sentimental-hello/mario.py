def main():
    try:
        userHeight = int(input("What is your height?\n"))
        # check for proper value, exclude negative integers
        if (userHeight > 0 and userHeight < 9):
            build(userHeight)
        else:
            main()
    # if input not an int, re-prompt the user
    except ValueError:
        print(main())


def build(height):
    # print the pyramid
    for i in range(height):
        print(" " * (height - 1), end="")
        print("#" * (i + 1), end="")
        height -= 1
        print()


main()
