#include "main.h"

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add the next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    // Check if the buffer is not empty
    if (*buff_ind > 0)
    {
        // Print the contents of the buffer to standard output
        write(1, &buffer[0], *buff_ind);
    }

    // Reset the buffer index to 0
    *buff_ind = 0;
}

/**
 * _printf - Printf function
 * @format: Format string
 * Return: Number of printed characters
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

    // Initialize the variable argument list
    va_start(list, format);

    // Iterate through each character in the format string
    for (i = 0; format && format[i] != '\0'; i++)
    {
        // Check if the current character is not '%'
        if (format[i] != '%')
        {
            // Add the character to the buffer
            buffer[buff_ind++] = format[i];

            // Check if the buffer is full and needs to be printed
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);

            // Increment the count of printed characters
            printed_chars++;
        }
        else
        {
            // Print the buffer before processing the format specifier
            print_buffer(buffer, &buff_ind);

            // Get the flags, width, precision, and size from the format string
            flags = get_flags(format, &i);
            width = get_width(format, &i, list);
            precision = get_precision(format, &i, list);
            size = get_size(format, &i);

            // Move to the next character in the format string
            ++i;

            // Handle the printing based on the format specifier
            printed = handle_print(format, &i, list, buffer, flags, width, precision, size);

            // Check for an error during printing
            if (printed == -1)
                return (-1);

            // Increment the count of printed characters
            printed_chars += printed;
        }
    }

    // Print any remaining characters in the buffer
    print_buffer(buffer, &buff_ind);

    // End the variable argument list
    va_end(list);

    // Return the total number of printed characters
    return (printed_chars);
}
