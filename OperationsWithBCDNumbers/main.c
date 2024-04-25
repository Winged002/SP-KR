#include <stdio.h>
#include "bcd_math.h"
 
int main() {
    int num1, num2;
    char op;
    char bcd_num[16];
    
    printf("Insert first number: ");
    scanf("%d", &num1);

    printf("Insert the operator: ");
    scanf(" %c", &op);

    printf("Insert second number: ");
    scanf("%d", &num2);

    long int result;
    result = bcd_calculate(num1, num2, op);
    printf("Result in decimal: %ld\n", result);

    decimal_to_bcd(result, bcd_num);
    int i;
    printf("Result in BCD: ");
    for (i = 0; i < 16; i++) {
        printf("%d", bcd_num[i]);
    }
    printf("\n");

    return 0;
}