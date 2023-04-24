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
	int valLen = 0, valCount = 0;

	valLen = _strlen(val);
	for (valCount = 0; valCount < valLen; valCount++)
	{
		_putchar((int)val[valCount]);
	}
	return valCount;
}
