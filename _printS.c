#include "main.h"

/**
 * _printS - writes the characters c to stdout
 * @val: The characters to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _printS(char *val)
{
	int i = 0;

	for (i = 0; val && val[i] != '\0'; i++)
	{
		_putchar((int)val[i]);
	}
	return i;
}
