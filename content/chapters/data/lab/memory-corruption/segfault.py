SIZE_INT = 32

def printBitArray(theBits):
    i = SIZE_INT-1;
    while i >= 0:
        print(theBits[i])
        i = i-1;

def toBits(value, inBits):
    shiftBit = 1;
    for i in range(SIZE_INT):
        if value & shiftBit == 0:
            inBits[i] = 0;
        else:
            inBits[i] = 1;
        shiftBit = shiftBit << 1;

def factorial(num):
    fact = 0
    if num == 0:
        return 1
    fact = factorial(num - 1)
    return fact*num

number = input("Input a positive integer: ")
fact = factorial(int(number))
print(number, " Factorial =", fact)
theBits = [0] * SIZE_INT
toBits(fact, theBits)
printBitArray(theBits)
