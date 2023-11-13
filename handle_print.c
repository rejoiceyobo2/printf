#include "main.h"

/**
 * handle_print - Prints an argument based on its type
 * by rejoice_yobo and Arohunmolase Daniel
 * @fmt: Formatted string in which to print the arguments.
 * @ind: Index in the format string.
 * @list: List of arguments to be printed.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 * Return: Number of characters printed (or -1 on error).
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
                 int flags, int width, int precision, int size)
{
    int unknow_len = 0;

    // Define a structure to represent format types
    typedef struct
    {
        char fmt;
        int (*fn)(va_list, char[], int, int, int, int);
    } fmt_t;

    // Array of format types
    fmt_t fmt_types[] = {
        {'c', print_char}, {'s', print_string}, {'%', print_percent},
        {'i', print_int}, {'d', print_int}, {'b', print_binary},
        {'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
        {'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
        {'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}};

    // Iterate through format types to find a match
    for (int i = 0; fmt_types[i].fmt != '\0'; i++)
    {
        if (fmt[*ind] == fmt_types[i].fmt)
        {
            return fmt_types[i].fn(list, buffer, flags, width, precision, size);
        }
    }

    // No matching format type found
    if (fmt_types[i].fmt == '\0')
    {
        if (fmt[*ind] == '\0')
        {
            return -1; // Unexpected end of format string
        }

        // Handle unknown format specifier %%
        unknow_len += write(1, "%%", 1);

        // Handle space character
        if (fmt[*ind - 1] == ' ')
        {
            unknow_len += write(1, " ", 1);
        }
        else if (width)
        {
            // Move back to check for width specification
            --(*ind);
            while (fmt[*ind] != ' ' && fmt[*ind] != '%')
            {
                --(*ind);
            }

            // Handle width specification
            if (fmt[*ind] == ' ')
            {
                --(*ind);
            }
            return 1;
        }

        // Write the unknown character
        unknow_len += write(1, &fmt[*ind], 1);
        return unknow_len;
    }

    return -1; // Error: Should not reach here
}

