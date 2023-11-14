#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a character
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_char(va_list types, char buffer[],
               int flags, int width, int precision, int size) {
    char c = va_arg(types, int);
    return handle_write_char(c, buffer, flags, width, precision, size);
}

/************************* PRINT A STRING *************************/

/**
 * print_string - Prints a string
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_string(va_list types, char buffer[],
                 int flags, int width, int precision, int size) {
    char *str = va_arg(types, char*);

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL)
        str = (precision >= 6) ? "      " : "(null)";

    int length = 0;
    while (str[length] && (precision < 0 || length < precision))
        buffer[length++] = str[length];

    return handle_write(buffer, length, flags, width);
}

/************************* PRINT PERCENT SIGN *************************/

/**
 * print_percent - Prints a percent sign
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list types, char buffer[],
                  int flags, int width, int precision, int size) {
    UNUSED(types);
    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    return write(1, "%%", 1);
}

/************************* PRINT INT *************************/

/**
 * print_int - Prints an integer
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_int(va_list types, char buffer[],
              int flags, int width, int precision, int size) {
    long int n = convert_size_number(va_arg(types, long int), size);
    int is_negative = (n < 0) ? 1 : 0;
    unsigned long int num = (is_negative) ? (unsigned long int)(-n) : (unsigned long int)n;

    int i = handle_write_number(buffer, num, is_negative);
    return write_number(is_negative, i, buffer, flags, width, precision, size);
}

/************************* PRINT BINARY *************************/

/**
 * print_binary - Prints a binary representation of an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_binary(va_list types, char buffer[],
                 int flags, int width, int precision, int size) {
    unsigned int n = va_arg(types, unsigned int);
    unsigned int a[32], m = 2147483648; /* (2 ^ 31) */

    for (int i = 0; i < 32; ++i, m >>= 1)
        a[i] = (n / m) % 2;

    int count = 0;
    for (int i = 0, sum = 0; i < 32; ++i) {
        sum += a[i];
        if (sum || i == 31) {
            write(1, &a[i] + '0', 1);
            count++;
        }
    }

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    return count;
}
