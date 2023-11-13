#include "main.h"

// Function prototypes
void print_buffer(char buffer[], int *buff_ind);
int handle_print(const char *format, int *index, va_list list, char buffer[],
                 int flags, int width, int precision, int size);

/**
 * _printf - Printf function
 * @format: format string
 * by rejoice_yobo and Arohunmolase Daniel.
 * _printf - Printf function.
 * @format: format.
 * Return: Printed chars.
 * Conditions: if else statement.
 */
int _printf(const char *format, ...)
{
    if (format == NULL)
        return -1;

    int printed_chars = 0;
    int buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    va_start(list, format);

    for (int i = 0; format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            // Handle regular characters
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            printed_chars++;
        }
        else
        {
            // Handle format specifiers
            print_buffer(buffer, &buff_ind);
            int flags = get_flags(format, &i);
            int width = get_width(format, &i, list);
            int precision = get_precision(format, &i, list);
            int size = get_size(format, &i);
            i++; // Move to the next character after the '%'
            int printed = handle_print(format, &i, list, buffer, flags, width, precision, size);
            if (printed == -1)
            {
                va_end(list);
                return -1; // Error in handling the format specifier
            }
            printed_chars += printed;
        }
    }

    print_buffer(buffer, &buff_ind);

    va_end(list);

    return printed_chars;
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add the next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
    {
        write(1, buffer, *buff_ind);
        *buff_ind = 0;
    }
}

