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
	int valCount = 0;

	for (valCount = 0; val && val[i] != '\0'; valCount++)
	{
		_putchar((int)val[valCount]);
	}
	return valCount;
}
