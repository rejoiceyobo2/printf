#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Custom implementation of the printf function
 * @format: Format string containing conversion specifiers
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	// Check if format is NULL
	if (format == NULL)
		return (-1);

	// Initialize the variable argument list
	va_start(list, format);

	// Loop through each character in the format string
	for (i = 0; format && format[i] != '\0'; i++)
	{
		// If the current character is not '%', add it to the buffer
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];

			// If the buffer is full, print its contents and reset the index
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);

			// Increment the count of characters printed
			printed_chars++;
		}
		else
		{
			// If the current character is '%', process the format specifier
			print_buffer(buffer, &buff_ind);

			// Get the flags, width, precision, and size from the format specifier
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);

			// Move to the next character after the '%'
			++i;

			// Handle the conversion based on the format specifier
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);

			// If an error occurred during printing, return -1
			if (printed == -1)
				return (-1);

			// Increment the count of characters printed
			printed_chars += printed;
		}
	}

	// Print any remaining characters in the buffer
	print_buffer(buffer, &buff_ind);

	// End the variable argument list
	va_end(list);

	// Return the total number of characters printed
	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of characters representing the buffer
 * @buff_ind: Pointer to the index at which to add the next character, represents the length
 */
void print_buffer(char buffer[], int *buff_ind)
{
	// Check if the buffer contains any characters
	if (*buff_ind > 0)
		// Print the contents of the buffer
		write(1, &buffer[0], *buff_ind);

	// Reset the buffer index to 0
	*buff_ind = 0;
}
