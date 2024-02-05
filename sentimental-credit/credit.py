def main():
    # take input form the user
    card = input("Number: ")

    if not card.isdigit() or len(card) not in [13, 15, 16]:
        print("INVALID")
        return

    if check(card):
        whichcard(card)
        return

    else:
        print("INVALID")
        return


def check(card):
    l = len(card)
    sum1 = []
    sum2 = []
    if l % 2 == 0:
        for i in range(int(l / 2)):
            # for even places:
            x = int(card[(i * 2)]) * 2
            if len(str(x)) > 1:
                for c in str(x):
                    sum1.append(int(c))
            else:
                sum1.append(x)

            # for odd places
            y = int(card[1 + (i * 2)])
            sum2.append(y)

    else:
        for i in range(int(l / 2)):
            # for odd places:
            x = (int(card[1 + (i * 2)])) * 2
            if len(str(x)) > 1:
                for c in str(x):
                    sum1.append(int(c))
            else:
                sum1.append(x)

            # for even places
            y = int(card[(i * 2)])
            sum2.append(y)

        # appending the last element
        sum2.append(int(card[l - 1]))

    # the final sum
    sumt = sum(sum1) + sum(sum2)
    # check if satisfies luhn's algo
    if sumt % 10 == 0:
        return True
    else:
        return False


def whichcard(card):
    cards = {
        4: "VISA",
        34: "AMEX",
        37: "AMEX",
        51: "MASTERCARD",
        52: "MASTERCARD",
        53: "MASTERCARD",
        54: "MASTERCARD",
        55: "MASTERCARD",
    }

    if card[0] == "4" and len(card) in [13, 16]:
        print(cards[4])
        return

    elif int(card[0:2]) in cards.keys():
        if len(card) == 15:
            print(cards[int(card[0:2])])
            return

        elif len(card) == 16:
            print(cards[int(card[0:2])])

        else:
            print("INVALID")
            return

    else:
        print("INVALID")
        return


# call to the main
main()
