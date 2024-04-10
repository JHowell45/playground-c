#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_CAPACITY 5
#define ORIGIN_INDEX 0

#define BYTE_CAPACITY 7

#define MAX_VALUE 255

typedef struct byte {
    size_t capacity;
    bool sign;
    int *bits;
} byte;

byte * newByte(void) {
    byte *b = malloc(sizeof(byte));

    b->capacity = BYTE_CAPACITY;
    b->sign = 0;
    b->bits = calloc(b->capacity, sizeof(int));
    return b;
}

byte * byteFromInt(int value) {
    byte *b = newByte();
    unsigned char num = (unsigned char)value;
    printf("Bytecode for int: %hhx\n", num);
    return b;
}

void showbits( unsigned int x )
{
    int i=0;
    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}

int ipow(int base, int exp) {
    int result = 1;
    for (;;) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }
    return result;
}

int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int byteAsInt(byte *b) {
    size_t exp = 0;
    int number = 0;
    for (int i = b->capacity; i >= 0; i--) {
        number += b->bits[i] * power(2, exp);
        exp++;
    }
    if (b->sign == 1) {
        number = -number;
    }
    return number;
}

void printByte(byte *b) {
    printf("%d", b->sign);
    for (int i = 0; i < b->capacity; i++) {
        printf("%d", b->bits[i]);
    }
    printf("\n");
}

void maxByte(byte *b) {
    for (int i = b->capacity; i >= 0; i--) {
        b->bits[i] = 1;
    }
}

void printAddresses(int *ptr, size_t length) {
    printf("[%p", ptr);
    for (int i = 1; i < length; i++) {
        ptr++;
        printf(", %p", ptr);
    }
    printf("]\n");
}

void printArray(int *ptr, size_t length) {
    printf("[%d", *ptr);
    for (int i = 1; i < length; i++) {
        ptr++;
        printf(", %d", *ptr);
    }
    printf("]\n");
}

void printManualArray(void *ptr, size_t length, size_t byteSize) {
    printf("Manual increment array with byte size of %zu:\n", byteSize);
    printf("[%d(%p)", *(int *)ptr, (int *)ptr);
    for (int i = 1; i < length; i++) {
        int *addr = ptr + (byteSize * (i - ORIGIN_INDEX));
        printf(", %d(%p)", *addr, addr);
    }
    printf("]\n\n");
}

void testArrays(void) {
    int x[ARRAY_CAPACITY] = {0,1,2,3,4};
    // By removing the type we can correctly increment by the specific number of bytes:
    void *rootPtr = x;
    int *ptr = x;
    printAddresses(ptr, ARRAY_CAPACITY);
    printArray(ptr, ARRAY_CAPACITY);

    printManualArray(ptr, ARRAY_CAPACITY, sizeof(int));
    printManualArray(ptr, ARRAY_CAPACITY, 4);
    printManualArray(ptr, ARRAY_CAPACITY, 2);

    printAddresses(ptr, ARRAY_CAPACITY + 5);
    printArray(ptr, ARRAY_CAPACITY + 5);
}

void testBytesStruct(void) {
    byte *num = newByte();
    printf("The Byte Number: %d\n", byteAsInt(num));
    printByte(num);
    maxByte(num);
    printf("The Byte Number: %d\n", byteAsInt(num));
    printByte(num);
    byte *newNum = byteFromInt(2);
    printf("The Byte Number: %d\n", byteAsInt(newNum));
    
}

int main(void) {
    testArrays();
    // testBytesStruct();
    // for (int i = 0; i < MAX_VALUE; i++) {
    //     printf("Decimal: %d, Hexadecimal: %x, Octal: %o\n", i, i, i); 
    // } 
    return 0;
}