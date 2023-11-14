#include "main.h"

/**
 * is_printable - Evaluates if a char is printable.
 * by rejoice_yobo and Arohunmolase Daniel.
 * @c: Char to be evaluated.
 *
 * Return: 1 if c is printable, otherwise return 0.
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

