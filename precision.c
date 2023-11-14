#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string containing conversion specifiers
 * @i: Pointer to the current position in the format string
 * @list: Variable argument list
 *
 * Return: Precision value:
 *   -1: No precision specified
 *    n: Precision value where n is a positive integer
 */
int get_precision(const char *format, int *i, va_list list)
{
	// Move to the character after '%'
	int curr_i = *i + 1;
	int precision = -1;

	// Check if the precision specifier is present (indicated by the '.' character)
	if (format[curr_i] != '.')
		return (precision);

	// Initialize precision to 0
	precision = 0;

	// Iterate through characters in the format specifier after the '.'
	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		// If the current character is a digit, update the precision value
		if (is_digit(format[curr_i]))
		{
			precision *= 10;
			precision += format[curr_i] - '0';
		}
		// If the current character is '*', get precision from variable argument list
		else if (format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(list, int);
			break;
		}
		// Stop if a non-digit character is encountered
		else
			break;
	}

	// Update the position pointer to the last processed character
	*i = curr_i - 1;

	// Return the determined precision value
	return (precision);
}
