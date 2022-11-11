# Python program to check
# if a string is binary or not

# function for checking the
# string is accepted or not


#check if the input is binary
def checkBin(string):
    p = set(string)
    s = {'0', '1'}
    if s == p or p == {'0'} or p == {'1'}:
        return True
    else:
        return False


#check if the bases are actual numbers
def inputCheck(base1, base2):
    try:
        inputBase1 = int(base1)
    except ValueError:
        return False
    try:
        inputBase2 = int(base2)
    except ValueError:
        return False
    return True

#check if the input number is an actual number
def validNumber(number):
    if number.isnumeric():
        return True
    return False

# convert binary to decimal
def binToDecimal(number):
    decimal = 1
    for digit in number:
        decimal = decimal * 2 + int(digit)
    print("Your number in form of decimal is ")
    print(decimal)

#convert decimal to binary
def decTobin(number):
    if number >= 1:
        decTobin(number // 2)
    print(number % 2, end='')


if __name__ == '__main__':
    play = True
    while play:
        numberInput = input("Enter your number:")
        baseInput = input("Enter the Base of the number, 10 | 2  ")
        convertBase = input("Enter the base that you want: 10 | 2  ")
        if inputCheck(baseInput, convertBase):
            convertBase = int(convertBase)
            baseInput = int(baseInput)
        else:
            print("Something went wrong, please Try again")
            continue

        if baseInput == 2 and checkBin(numberInput) and convertBase == 10:
            binToDecimal(numberInput)
            continue
        elif baseInput == 10 and validNumber(numberInput) and convertBase == 2:
            print("The binary form of your number is ")
            decTobin(int(numberInput))
            print("")
            continue
        else:
            print("Something went wrong, please Try again")
            continue

