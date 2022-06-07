#include <stdio.h>

#define SIZE_INT 32

void printBitArray(unsigned int theBits[SIZE_INT])
{
    unsigned int i = SIZE_INT-1;
    while (i >= 0)
    {
        printf("%u\n", theBits[i]);
        i--;
    }
}

void toBits(unsigned int value, unsigned int inBits[SIZE_INT])
{
    unsigned int shiftBit = 0x0001;

    for(unsigned int i = 0; i < SIZE_INT; i++)
    {
        if ((value & shiftBit) == 0)
            inBits[i] = 0;
        else
            inBits[i] = 1;
        shiftBit = shiftBit << 1;
    }
}

unsigned int factorial(unsigned int num)
{
    unsigned int fact = 0;

    if (num == 0)
        return 1;

    fact = factorial(num-1);
    return fact*num;
}

int main()
{
    unsigned int number = 0;
    unsigned int theBits[SIZE_INT];
    unsigned int fact;

    printf("Input a positive integer: ");
    scanf("%u", &number);

    fact = factorial(number);
    printf("%u   Factorial = %u \n", number, fact);

    toBits(fact, theBits);
    printBitArray(theBits);

    return 0;
}
