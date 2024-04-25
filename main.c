#include <stdio.h>
#include <stdbool.h>
#include "bcdopps.h"

int main() {
    int a, b;
    char sign;
    while (true) {
        printf("Enter first number: \n");
        scanf("%d", &a);
        printf("Enter operation sign \n");
        scanf(" %c", &sign);
        printf("Enter second number \n");
        scanf("%d", &b);
        switch (sign) {
            case '+':
                add(a, b);
                break;
            case '-':
                sub(a, b);
                break;
            case '*':
                mul(a, b);
                break;
            case '/':
                divide(a, b);
                break;
            case '^':
                power(a, b);
                break;
            default:
                printf("Please enter correct operation sign \n");
                break;
        }
    }
    return 0;
}
