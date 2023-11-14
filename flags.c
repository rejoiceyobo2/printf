#include "main.h"

/**
 * get_flags - Extracts and calculates active flags from the format specifier
 * @format: Format string containing conversion specifiers
 * @i: Pointer to the current position in the format string
 * 
 * Return: Integer representing active flags:
 *   F_MINUS: Left-align the output
 *   F_PLUS: Forces a plus sign (+) in front of positive numbers
 *   F_ZERO: Left-pads the number with zeroes instead of spaces
 *   F_HASH: Used with o, x or X specifiers, the value is preceded with 0, 0x or 0X respectively
 *   F_SPACE: If no sign is going to be written, a blank space is inserted before the value
 */
int get_flags(const char *format, int *i)
{
	// Array of characters representing valid flags in the format specifier
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	// Corresponding values for each flag
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	int j, curr_i;
	int flags = 0;

	// Iterate through characters in the format specifier starting from the position after '%'
	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		// Check if the current character is one of the valid flags
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
		{
			if (format[curr_i] == FLAGS_CH[j])
			{
				// If found, set the corresponding flag in the 'flags' variable
				flags |= FLAGS_ARR[j];
				break;
			}
		}

		// If the current character is not a valid flag, exit the loop
		if (FLAGS_CH[j] == 0)
			break;
	}

	// Update the position pointer to the last processed character
	*i = curr_i - 1;

	// Return the calculated flags
	return (flags);
}
