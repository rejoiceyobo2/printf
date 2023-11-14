#include "main.h"

/**
 * is_printable - Checks if a character is printable
 * @c: Character to be evaluated.
 *
 * Return: 1 if the character is printable, 0 otherwise
 */
int is_printable(char c)
{
	// Check if the character falls within the printable ASCII range
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Appends ASCII in hexadecimal code to a buffer
 * @buffer: Array of characters.
 * @i: Index at which to start appending.
 * @ascii_code: ASCII code to be converted to hexadecimal.
 *
 * Return: Always 3 (length of the hexadecimal code)
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexadecimal format code is always 2 digits long */

	// Ensure non-negative representation
	if (ascii_code < 0)
		ascii_code *= -1;

	// Append the escape sequence '\x' and the hexadecimal representation to the buffer
	buffer[i++] = '\\';
	buffer[i++] = 'x';
	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Checks if a character is a digit
 * @c: Character to be evaluated
 *
 * Return: 1 if the character is a digit, 0 otherwise
 */
int is_digit(char c)
{
	// Check if the character is within the numeric ASCII range
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @num: Number to be casted.
 * @size: Size indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convert_size_number(long int num, int size)
{
	// Cast the number based on the specified size
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Casts an unsigned number to the specified size
 * @num: Number to be casted
 * @size: Size indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	// Cast the unsigned number based on the specified size
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
