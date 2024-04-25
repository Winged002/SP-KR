#include <stdio.h>
#include <ctype.h>
#include <math.h>
 
long int bcd_addition(int num1, int num2);
long int bcd_subtraction(int num1, int num2);
long int bcd_multiplication(int num1, int num2);
long int bcd_division(int num1, int num2);
long int bcd_exponentiation(int num1, int num2);

long int bcd_calculate(int num1, int num2, char operator) {
    if (num1 > 9999 || num2 > 9999) {
        printf("Error: Numbers must be 4-digit!\n");
        return -1;
    }
    long int result;
    switch (operator) {
        case '+':
            result = bcd_addition(num1, num2);
            break;
        case '-':
            result = bcd_subtraction(num1, num2);
            break;
        case '*':
            result = bcd_multiplication(num1, num2);
            break;
        case '/':
            result = bcd_division(num1, num2);
            break;
        case '^':
            result = bcd_exponentiation(num1, num2);
            break;
        default:
            printf("Error: Invalid operator '%c'\n", operator);
            return -1;
    }
    return result;
}

void decimal_to_bcd(long int decimal_num, char* bcd_num) {
    int i;

    for(i = 0; i < 4; i++) {
        int digit = (decimal_num / (int)pow(10, i)) % 10;
        bcd_num[4*i] = digit & 0x1;
        bcd_num[4*i+1] = (digit >> 1) & 0x1;
        bcd_num[4*i+2] = (digit >> 2) & 0x1;
        bcd_num[4*i+3] = (digit >> 3) & 0x1;
    }

 // Reverse the order of the BCD digits
    for(i = 0; i < 8; i++) {
        char temp = bcd_num[i];
        bcd_num[i] = bcd_num[15-i];
        bcd_num[15-i] = temp;
    }

}

long int bcd_addition(int num1, int num2) {
    long int result = 0;
    int carry = 0;
    for (int i = 0; i < 4; i++) {
        int digit1 = num1 % 10;
        int digit2 = num2 % 10;
        int sum = digit1 + digit2 + carry;
        carry = sum > 9 ? 1 : 0;
        sum = sum % 10;
        result += sum * pow(10, i);
        num1 /= 10;
        num2 /= 10;
    }
    return result;
}

long int bcd_subtraction(int num1, int num2) {
    long int result = 0;
    int borrow = 0;
    for (int i = 0; i < 4; i++) {
        int digit1 = num1 % 10;
        int digit2 = num2 % 10;
        int diff = digit1 - digit2 - borrow;
        borrow = diff < 0 ? 1 : 0;
        diff = (diff + 10) % 10;
        result += diff * pow(10, i);
        num1 /= 10;
        num2 /= 10;
    }
    return result;
}

long int bcd_multiplication(int num1, int num2) {
    long int result = 0;
    for (int i = 0; i < 4; i++) {
        int digit1 = num1 % 10;
        num1 /= 10;
        int temp = num2;
        int carry = 0;
        int partial_result = 0;
        for (int j = 0; j < 4; j++) {
            int digit2 = temp % 10;
            temp /= 10;
            int product = digit1 * digit2 + carry;
            carry = product / 10;
            product = product % 10;
            partial_result += product * pow(10, j);
        }
        result = bcd_addition(result, partial_result * pow(10, i));
    }
    return result;
}

long int bcd_division(int num1, int num2) {
    long int result = 0;
    int quotient = 0;
    int remainder = 0;
    for (int i = 3; i >= 0; i--) {
        int digit1 = (remainder * 10 + (num1 / (int) pow(10, i))) / num2;
        remainder = (remainder * 10 + (num1 / (int) pow(10, i))) % num2;
        quotient += digit1 * (int) pow(10, i);
    }
    result = quotient * 100 + remainder;
    return result;
}

long int bcd_exponentiation(int num1, int num2) {
    long int result = 1;
    for (int i = 0; i < num2; i++) {
    result = bcd_multiplication(result, num1);
    }
    return result;
}