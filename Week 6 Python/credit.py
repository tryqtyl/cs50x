# TODO
from cs50 import get_int
from cs50 import get_string

# Better to treat 'number' as 'string'
def main():
    while True:
        try:
            number = get_string("Number: ")
            if int(number):
                break
        except ValueError:
            continue
    if len(number) == 15 and valid(number) and (number[:2] in ["34", "37"]):
        print ("AMEX")
    elif len(number) == 16 and valid(number) and (number[:2] in ["51", "52", "53", "54", "55"]):
        print ("MASTERCARD")
    elif (len(number) in [13, 16]) and valid(number) and (number[:1] == "4"):
        print ("VISA")
    else:
        print ("INVALID")


def valid(number):
    number = number[::-1]
    sum = 0
    for i in range(0,len(number),2):
        if i == len(number) - 1:
            sum += int(number[i])
            break
        sum += (int(number[i])) + (((int(number[i + 1]) * 2) // 10)) + (int(number[i + 1]) * 2 % 10)
    if sum % 10 == 0:
        return True
    else:
        return False

main()