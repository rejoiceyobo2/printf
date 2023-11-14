#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a single character
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags (e.g., F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE)
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	// Delegate to handle_write_char to handle the printing details
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/

/**
 * print_string - Prints a string
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags (e.g., F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE)
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	// Handle the case where the string is NULL
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	// Calculate the length of the string
	while (str[length] != '\0')
		length++;

	// Apply precision to limit the number of characters printed
	if (precision >= 0 && precision < length)
		length = precision;

	// Handle width and alignment
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	// Print the string
	return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/

/**
 * print_percent - Prints a percent sign
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags (e.g., F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE)
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/

/**
 * print_int - Prints an integer
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags (e.g., F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE)
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	// Convert the number based on the size specifier
	n = convert_size_number(n, size);

	// Handle the case where the number is zero
	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	// Handle negative numbers
	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	// Convert the number to characters and handle writing details
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	// Delegate to write_number to handle the printing details
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/

/**
 * print_binary - Prints a binary representation of an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags (e.g., F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE)
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	// Extract the unsigned integer from the arguments
	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;

	// Generate the binary representation of the number
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}

	// Print the binary representation, excluding leading zeros
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];
			write(1, &z, 1);
			count++;
		}
	}

	return (count);
}
