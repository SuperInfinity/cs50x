import cs50


def main():
    text = cs50.get_string("Text: ")
    Coleman_Liau_formula(text)


def Coleman_Liau_formula(text):
    sentences = 0
    letters = 0
    words = len(text.split())

    for c in text:
        if c.isalpha():
            letters += 1

        elif c in ["!", "?", "."]:
            sentences += 1

    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
        return

    elif index >= 16:
        print("Grade 16+")
        return

    else:
        print(f"Grade {index}")


main()

# Would you like them here or there? I would not like them here or there. I would not like them anywhere.
