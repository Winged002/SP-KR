#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STR_LEN 256

bool unsigned_integer_decimal_number(const char *str) {
    // Checking for the optional '+' sign
    if (str[0] == '+') {
        str++; // Increment the pointer to skip the '+' sign
    }

    // Check if the first character is a digit between 1 and 9
    if (str[0] < '1' || str[0] > '9') {
        return false;
    }

    int len = strlen(str);
    int i = 1; // Start checking from the second character

    // Loop through the remaining characters
    for (; i < len; i++) {
        // If the current character is 'u' or 'U', it should be the last character in the string
        if (str[i] == 'u' || str[i] == 'U') {
            if (i == len - 1) {
                return true; // The string is valid
            } else {
                return false; // The 'u' or 'U' is not the last character, so the string is invalid
            }
        }
        
        // If the current character is not a digit, the string is invalid
        if (!isdigit(str[i])) {
            return false;
        }
    }

    // If the loop completes without finding a 'u' or 'U', the string is invalid
    return false;
}

bool signed_integer_decimal_number(const char *str) {
     // Check for an optional '+' or '-' sign at the beginning
    if (str[0] == '+' || str[0] == '-') {
        str++; // Increment the pointer to skip the sign
    }

    // Check if the first character is a digit between 1 and 9
    if (str[0] < '1' || str[0] > '9') {
        return false;
    }

    int len = strlen(str);
    for (int i = 1; i < len; i++) {
        // Check if the current character is a digit, otherwise return false
        if (!isdigit(str[i])) {
            return false;
        }
    }

    return true;
}

bool is_hex_digit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

bool hexadecimal_integer_number(const char *str){
    // Check for an optional '+' or '-' sign at the beginning
    if (str[0] == '+' || str[0] == '-') {
        str++; // Increment the pointer to skip the sign
    }

    // Check if the string starts with '0x' or '0X'
    if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X')) {
        return false;
    }

    str += 2; // Increment the pointer to skip the '0x' or '0X'

    // If there are no more characters after '0x' or '0X', the string is invalid
    if (*str == '\0') {
        return false;
    }

    while (*str != '\0') {
        // If the current character is not a valid hex digit, the string is invalid
        if (!is_hex_digit(*str)) {
            return false;
        }
        str++;
    }

    return true;
}

bool binary_integer_number(const char *str){
    // Check for an optional '+' or '-' sign at the beginning
    if (str[0] == '+' || str[0] == '-') {
        str++; // Increment the pointer to skip the sign
    }

    // Check if the string starts with '0b' or '0B'
    if (str[0] != '0' || (str[1] != 'b' && str[1] != 'B')) {
        return false;
    }

    str += 2; // Increment the pointer to skip the '0b' or '0B'

    // If there are no more characters after '0b' or '0B', the string is invalid
    if (*str == '\0') {
        return false;
    }

    while (*str != '\0') {
        // If the current character is not a binary digit (0 or 1), the string is invalid
        if (str[0] != '0' && str[0] != '1') {
            return false;
        }
        str++;
    }

    return true;
}

bool octal_integer_number(const char *str){
    // Check for an optional '+' or '-' sign at the beginning
    if (str[0] == '+' || str[0] == '-') {
        str++; // Increment the pointer to skip the sign
    }

    // Check if the string starts with '0'
    if (str[0] != '0') {
        return false;
    }

    str++; // Increment the pointer to skip the '0'

    // If there are no more characters after '0', the string is invalid
    if (*str == '\0') {
        return false;
    }

    while (*str != '\0') {
        // If the current character is not an octal digit (0 to 7), the string is invalid
        if (str[0] < '0' || str[0] > '7') {
            return false;
        }
        str++;
    }

    return true;
}

bool double_number(const char *str) {
     if (str[0] == '+' || str[0] == '-') {
        str++;
    }

    bool has_digit = false;
    bool has_dot = false;
    bool has_e = false;

    while (*str != '\0') {
        if (isdigit(*str)) {
            has_digit = true;
        } else if (*str == '.' && !has_dot && !has_e) {
            has_dot = true;
        } else if ((*str == 'e' || *str == 'E') && !has_e && has_digit) {
            has_e = true;
            has_digit = false; // Reset for digits after 'e' or 'E'
            str++;

            if (*str == '-' || *str == '+') {
                str++;
            }
            continue;
        } else {
            return false;
        }
        str++;
    }

    if (has_e && !has_digit) {
        return false;
    }

    return has_digit && has_dot;
}

bool float_number(const char *str) {
    if (str[0] == '+' || str[0] == '-') {
        str++;
    }

    bool has_digit = false;
    bool has_dot = false;
    bool has_e = false;

    while (*str != '\0') {
        if (isdigit(*str)) {
            has_digit = true;
        } else if (*str == '.' && !has_dot && !has_e) {
            has_dot = true;
        } else if ((*str == 'e' || *str == 'E') && !has_e && has_digit) {
            has_e = true;
            has_digit = false; // Reset for digits after 'e' or 'E'
            str++;

            if (*str == '-' || *str == '+') {
                str++;
            }
            continue;
        } else if (*str == 'f' || *str == 'F') {
            break;
        } else {
            return false;
        }
        str++;
    }

    if (has_e && !has_digit) {
        return false;
    }

     // Check if the string ends with 'f' or 'F'
    if (*str == 'f' || *str == 'F') {
        str++;
        if (*str == '\0') {
            return has_digit && has_dot;
        }
    }

    return false;
}

bool long_double_number(const char *str) {
    if (str[0] == '+' || str[0] == '-') {
        str++;
    }

    bool has_digit = false;
    bool has_dot = false;
    bool has_e = false;

    while (*str != '\0') {
        if (isdigit(*str)) {
            has_digit = true;
        } else if (*str == '.' && !has_dot && !has_e) {
            has_dot = true;
        } else if ((*str == 'e' || *str == 'E') && !has_e && has_digit) {
            has_e = true;
            has_digit = false; // Reset for digits after 'e' or 'E'
            str++;

            if (*str == '-' || *str == '+') {
                str++;
            }
            continue;
        } else if (*str == 'l' || *str == 'L' || *str == 'a'|| *str == 'b') {
            break;
        } else {
            return false;
        }
        str++;
    }

    if (has_e && !has_digit) {
        return false;
    }

     // Check if the string ends with 'f' or 'F'
    if (*str == 'l' || *str == 'L' || *str == 'a'|| *str == 'b') {
        str++;
        if (*str == '\0') {
            return has_digit && has_dot;
        }
    }

    return false;
}

bool long_unsigned_integer_decimal_number(const char *str) {
    if (str[0] == '+') {
        if (str[1] < '1' || str[1] > '9') {
            return false;
        }
        str++;
    } else if (str[0] < '1' || str[0] > '9') {
        return false;
    }

    size_t len = strlen(str);
    for (size_t i = 1; i < len - 2; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    char last = tolower(str[len - 1]);
    char second_last = tolower(str[len - 2]);

    if ((last == 'u' && second_last == 'l') || (last == 'l' && second_last == 'u')) {
        return true;
    }

    return false;
}

bool long_signed_integer_decimal_number(const char *str) {
     if (str[0] == '+' || str[0] == '-') {
        if (str[1] < '1' || str[1] > '9') {
            return false;
        }
        str++;
    } else if (str[0] < '1' || str[0] > '9') {
        return false;
    }

    size_t len = strlen(str);
    for (size_t i = 1; i < len - 1; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    if (str[len - 1] == 'l' || str[len - 1] == 'L') {
        return true;
    }

    return false;
}

bool long_long_unsigned_integer_decimal_number(const char *str) {
    if (str[0] == '+') {
        if (str[1] < '1' || str[1] > '9') {
            return false;
        }
        str++;
    } else if (str[0] < '1' || str[0] > '9') {
        return false;
    }

    size_t len = strlen(str);
    for (size_t i = 1; i < len - 3; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    char u = tolower(str[len - 3]);
    char l1 = tolower(str[len - 2]);
    char l2 = tolower(str[len - 1]);

    if ((u == 'u' && l1 == 'l' && l2 == 'l') || (u == 'l' && l1 == 'l' && l2 == 'u')) {
        return true;
    }

    return false;
}

bool long_long_signed_integer_decimal_number(const char *str) {
    if (str[0] == '+' || str[0] == '-') {
        if (str[1] < '1' || str[1] > '9') {
            return false;
        }
        str++;
    } else if (str[0] < '1' || str[0] > '9') {
        return false;
    }

    size_t len = strlen(str);
    for (size_t i = 1; i < len - 2; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    char l1 = tolower(str[len - 2]);
    char l2 = tolower(str[len - 1]);

    if (l1 == 'l' && l2 == 'l') {
        return true;
    }

    return false;
}

char *read_and_return_string(FILE *file) {
    char *str = (char *)malloc(MAX_STR_LEN * sizeof(char));
    int index = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            if (index > 0) {
                break;
            }
            continue;
        }

        str[index++] = ch;
        if (index >= MAX_STR_LEN - 1) {
            break;
        }
    }

    if (index == 0 && ch == EOF) {
        free(str);
        return NULL;
    }

    str[index] = '\0';
    return str;
}

int main() {
    const char *input_file = "input.txt";
    FILE *file = fopen(input_file, "r");
 
    int count_unsigned_integer_decimal_number = 0;
    int count_signed_integer_decimal_number = 0;
    int count_hexadecimal_integer_number = 0;
    int count_binary_integer_number = 0;
    int count_octal_integer_number = 0;
    int count_double_number = 0;
    int count_float_number = 0;
    int count_long_double_number = 0;
    int count_long_unsigned_integer_decimal_number = 0;
    int count_long_signed_integer_decimal_number = 0;
    int count_long_long_unsigned_integer_decimal_number = 0;
    int count_long_long_signed_integer_decimal_number = 0;

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    char *str;
    while ((str = read_and_return_string(file)) != NULL)
    {
        // Process the string here and do something with it
        if (unsigned_integer_decimal_number(str))
        {
            count_unsigned_integer_decimal_number++;
        }
        else
        {
            if (signed_integer_decimal_number(str))
            {
                count_signed_integer_decimal_number++;
            }
            else
            {
                if (hexadecimal_integer_number(str))
                {
                count_hexadecimal_integer_number++;
                }
                else
                {
                if (binary_integer_number(str))
                {
                    count_binary_integer_number++;
                }
                else
                {
                    if (octal_integer_number(str))
                    {
                        count_octal_integer_number++;
                    }
                    else
                    {
                        if (double_number(str))
                        {
                            count_double_number++;
                        }
                        else
                        {
                            if (float_number(str))
                            {
                                count_float_number++;
                            }
                            else
                            {
                                if (long_double_number(str))
                                {
                                    count_long_double_number++;
                                }
                                else
                                {
                                    if (long_unsigned_integer_decimal_number(str))
                                    {
                                        count_long_unsigned_integer_decimal_number++;
                                    }
                                    else
                                    {
                                        if (long_signed_integer_decimal_number(str))
                                        {
                                            count_long_signed_integer_decimal_number++;
                                        }
                                        else
                                        {
                                            if (long_long_unsigned_integer_decimal_number(str))
                                            {
                                                count_long_long_unsigned_integer_decimal_number++;
                                            }
                                            else
                                            {
                                                if (long_long_signed_integer_decimal_number(str))
                                                {
                                                    count_long_long_signed_integer_decimal_number++;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                }
            }
        }
        free(str);
    }

    fclose(file);
    
    printf("UNSIGNED INTEGER DECIMAL NUMBERS: %d\n", count_unsigned_integer_decimal_number);
    printf("SIGNED INTEGER DECIMAL NUMBERS: %d\n", count_signed_integer_decimal_number);
    printf("HEXADECIMAL INTEGER NUMBERS: %d\n", count_hexadecimal_integer_number);
    printf("BINARY INTEGER NUMBERS: %d\n", count_binary_integer_number);
    printf("OCTAL INTEGER NUMBERS: %d\n", count_octal_integer_number);
    printf("DOUBLE NUMBERS: %d\n", count_double_number);
    printf("FLOAT NUMBERS: %d\n", count_float_number);
    printf("LONG DOUBLE NUMBERS: %d\n", count_long_double_number);
    printf("LONG UNSIGNED INTEGER DECIMAL NUMBERS: %d\n", count_long_unsigned_integer_decimal_number);
    printf("LONG SIGNED INTEGER DECIMAL NUMBERS: %d\n", count_long_signed_integer_decimal_number);
    printf("LONG LONG UNSIGNED INTEGER DECIMAL NUMBERS: %d\n", count_long_long_unsigned_integer_decimal_number);
    printf("LONG LONG SIGNED INTEGER DECIMAL NUMBERS: %d\n", count_long_long_signed_integer_decimal_number);
    
    return 0;
}


