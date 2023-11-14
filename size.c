#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string containing conversion specifiers
 * @i: Pointer to the current position in the format string
 *
 * Return: Size specifier:
 *   S_LONG: Indicates a long-sized argument
 *   S_SHORT: Indicates a short-sized argument
 */
int get_size(const char *format, int *i)
{
	// Move to the character after '%'
	int curr_i = *i + 1;
	int size = 0;

	// Check if the size specifier is 'l' for long
	if (format[curr_i] == 'l')
		size = S_LONG;
	// Check if the size specifier is 'h' for short
	else if (format[curr_i] == 'h')
		size = S_SHORT;

	// If size is not found, update the position pointer to the last processed character
	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	// Return the determined size specifier
	return (size);
}
