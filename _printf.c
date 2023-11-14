#include "main.h"

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add the next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: Format string.
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
    int i, printed = 0, printed_chars = 0;
    int flags, width, precision, size, buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    // Check if the format string is NULL
    if (format == NULL)
        return (-1);

    // Start the variable argument list
    va_start(list, format);

    // Loop through the format string
    for (i = 0; format && format[i] != '\0'; i++)
    {
        // If the character is not '%', add it to the buffer
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            // If the buffer is full, print its contents
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            printed_chars++;
        }
        else
        {
            // Print the buffer contents
            print_buffer(buffer, &buff_ind);
            // Get formatting information and handle the print
            flags = get_flags(format, &i);
            width = get_width(format, &i, list);
            precision = get_precision(format, &i, list);
            size = get_size(format, &i);
            ++i;
            printed = handle_print(format, &i, list, buffer,
                                   flags, width, precision, size);
            // If an error occurs during printing, return -1
            if (printed == -1)
                return (-1);
            printed_chars += printed;
        }
    }

    // Print any remaining contents in the buffer
    print_buffer(buffer, &buff_ind);

    // End the variable argument list
    va_end(list);

    // Return the total number of characters printed
    return (printed_chars);
}
