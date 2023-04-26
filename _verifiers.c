#include "main.h"

/**
 * _canPrint - Check if a char is printable
 * @c: Char to be evaluated.
 *
 * Return: 1 if true, else 0
 */
int _canPrint(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @b: Array of chars.
 * @i: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char b[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* Hexa format can only be 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	b[i++] = '\\';
	b[i++] = 'x';

	b[i++] = map_to[ascii_code / 16];
	b[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * _hasDigit - Checks if a char is a digit
 * @c: Char to be evaluated
 *
 * Return: 1 if true, else 0
 */
int _hasDigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * size_to_number - Turns number to the specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: New value of num
 */
long int size_to_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
