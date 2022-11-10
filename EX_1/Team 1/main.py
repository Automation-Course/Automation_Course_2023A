
def bintodec():
    print("Enter the Binary Number: ", end="")
    bnum = int(input())

    decnum = 0
    pow = 1
    binlen = len(str(bnum))

    for k in range(binlen):
        remain = bnum % 10
        decnum = decnum + (remain * pow)
        pow = pow * 2
        bnum = int(bnum/10)

    print("\nEquivalent Decimal Value = ", decnum)

def decimalToBinary(num):
    if num > 1:
        decimalToBinary(num // 2) ##Return the number of times 2 enters in 'num'
    print(num % 2, end='')


indicator = int(input("Enter 1 for Decimal to Binary or 0 for binary to Decimal: "))
if indicator == 0:
    bintodec()
else:
    number = int(input("Enter any decimal number: "))
    decimalToBinary(number)




