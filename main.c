#include <limits.h>
#include <stdio.h>
#include "main.h"

/**
 * main - Entry point
 *
 * Return: Always return 0
 */
int main(void)
{
    int len;
    int len2;
    unsigned int ui;
    void *addr;

    // Test case 1
    len = _printf("Let's try to printf a simple sentence.\n");
    len2 = printf("Let's try to printf a simple sentence.\n");
    printf("Length:[%d, %i]\n", len, len);
    printf("Length:[%d, %i]\n", len2, len2);

    // Test case 2
    _printf("Negative:[%d]\n", -762534);
    printf("Negative:[%d]\n", -762534);

    // Test case 3
    ui = (unsigned int)INT_MAX + 1024;
    _printf("Unsigned:[%u]\n", ui);
    printf("Unsigned:[%u]\n", ui);
    _printf("Unsigned octal:[%o]\n", ui);
    printf("Unsigned octal:[%o]\n", ui);
    _printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
    printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);

    // Test case 4
    _printf("Character:[%c]\n", 'H');
    printf("Character:[%c]\n", 'H');

    // Test case 5
    _printf("String:[%s]\n", "I am a string !");
    printf("String:[%s]\n", "I am a string !");

    // Test case 6
    addr = (void *)0x7ffe637541f0;
    _printf("Address:[%p]\n", addr);
    printf("Address:[%p]\n", addr);

    // Test case 7
    len = _printf("Percent:[%%]\n");
    len2 = printf("Percent:[%%]\n");
    _printf("Len:[%d]\n", len);
    printf("Len:[%d]\n", len2);

    // Test case 8 (unknown specifier)
    _printf("Unknown:[%r]\n");
    printf("Unknown:[%r]\n");

    return (0);
}

