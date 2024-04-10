#include <stdlib.h>
#include <stdio.h>

void printBitwiseTest(int a, int b) {
    printf("a: %d, b: %d\n", a, b);
    printf("AND - a & b: %d\n", a & b);
    printf("OR - a | b: %d\n", a | b);
    printf("XOR - a ^ b: %d\n", a ^ b);
    printf("\n\n");
}

int main(void) {
    printBitwiseTest(0, 0);
    printBitwiseTest(1, 0);
    printBitwiseTest(0, 1);
    printBitwiseTest(1, 1);
}