from cs50 import get_int

# take input from rthe user for height
while True:
    h = get_int("Height: ")
    if h >= 1 and h <= 8:
        break

# print the blocks
for i in range(h):
        print(" " * (h - i - 1), end = "")
        print("#" * (i + 1), end = "  ")
        print("#" * (i + 1))
