def main():

    text = str(input("Text: "))
    countAllWords(text)


def countAllWords(text):
    # initiate all variables that will be used
    letters = sentences = words = spaces = 0
    indexT = indexL = indexS = 0.0
    # remove spaces and store in a separate string
    nospaces = text.replace(" ", "")

    for i in range(len(nospaces)):
        # is character a letter
        if nospaces[i].isalpha():
            letters += 1
        # find end of sentence
        elif nospaces[i] in [".", "!", "?"]:
            sentences += 1
        else:
            pass

    # formula borrowed from readability.c, removed rounding and float
    words = len(text.split())  # Count words
    indexL = (letters / words) * 100
    indexS = (sentences / words) * 100
    indexT = 0.0588 * indexL - 0.296 * indexS - 15.8
    printTo(round(indexT))


def printTo(index):
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()
