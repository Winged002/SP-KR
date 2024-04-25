#include "bcdopps.h"
#include <stdio.h>
#include <math.h>

void add(int a, int b) {
    printf("Sum equals: %d\n", a + b);
    decimalToBcd(a + b);
}

void sub(int a, int b) {
    printf("Subtraction equals: %d\n", a - b);
    decimalToBcd(a - b);
}

void mul(int a, int b) {
    printf("Multiplication equals: %d\n", a * b);
    decimalToBcd(a * b);
}

void divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return;
    }
    printf("Division equals: %d\n", a / b);
    decimalToBcd(a / b);
}

void power(int a, int b) {
    int n = pow(a, b);
    printf("Power equals: %d\n", n);
    decimalToBcd(pow(a, b));
}

void decimalToBcd(int a) {
    char bcdNum[50] = {'0'};
    int n = 0, i = 0, refA = a;
    while (refA > 0) {
        refA /= 10;
        i++;
    }
    int index = i * 4;
    for (int x = i; x > 0; x--) {
        n = a % 10;
        for (int j = 0; j < 4; j++) {
            bcdNum[index] = n % 2;
            n /= 2;
            index--;
        }
        a /= 10;
    }
    index = 1;
    for (int x = i; x > 0; x--) {
        for (int y = 0; y < 4; y++) {
            printf("%c", bcdNum[index] + '0');
            index++;
        }
        printf(" ");
    }
    printf("\n");
}
