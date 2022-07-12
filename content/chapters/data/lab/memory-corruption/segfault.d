import std.stdio;

enum SIZE_INT = 32;

void printBitArray(uint[SIZE_INT] theBits)
{
    uint i = SIZE_INT-1;
    while (i >= 0)
    {
        printf("%u\n",theBits[i]);
        i--;
    }
}

void toBits(uint value, uint[SIZE_INT] inBits)
{
    uint shiftBit = 0x0001;

    for(uint i = 0; i < SIZE_INT; i++)
    {
        if ((value & shiftBit) == 0)
            inBits[i] = 0;
        else
            inBits[i] = 1;
        shiftBit = shiftBit << 1;
    }

}

uint factorial(uint num)
{
    uint fact = 0;

    if (num == 0)
        return 1;

    fact = factorial(num-1);
    return fact*num;
}

int main()
{
    uint number = 0;
    uint[SIZE_INT] theBits;
    uint fact;

    printf("Input a positive integer: ");
    scanf("%u", &number);

    fact = factorial(number);
    printf("%u   Factorial = %u \n", number, fact);

    toBits(fact, theBits);
    printBitArray(theBits);

    return 0;
}
