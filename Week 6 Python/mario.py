# TODO
def get_height():
    while True:
        try:
            height = int(input("Height: "))
            if height > 0 and height < 9:
                break
        except ValueError:
            print("That's not an integer!")
    return height


def main():
    h = get_height()
    for i in range(1, h + 1):
        print(" " * (h - i) + "#" * i + "  " + "#" * i)


main()