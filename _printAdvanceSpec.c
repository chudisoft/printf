#include "main.h"

/* PRINT UNSIGNED NUMBER */

/**
 * _printU - Prints an unsigned number
 * @types: List of arguments
 * @b: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @_prec: Precision specification
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */

int _printU(va_list types, char b[],
		int flags, int width, int _prec, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		b[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, b, flags, width, _prec, size));
}

/* PRINT UNSIGNED NUMBER IN OCTAL */

/**
 * _printO - Prints an unsigned number in octal notation
 * @types: List of arguments
 * @b: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @_prec: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */

int _printO(va_list types, char b[],
		int flags, int width, int _prec, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		b[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		b[i--] = '0';

	i++;

	return (write_unsgnd(0, i, b, flags, width, _prec, size));
}

/* PRINT UNSIGNED NUMBER IN HEXADECIMAL */

/**
 * _printH - Prints an unsigned number in hexadecimal notation
 * @types: List of arguments
 * @b: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @_prec: Precision specification
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */

int _printH(va_list types, char b[],
		int flags, int width, int _prec, int size)
{
	return (print_hexa(types, "0123456789abcdef", b,
				flags, 'x', width, _prec, size));
}

/* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL */

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: List of arguments
 * @b: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @_prec: Precision specification
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */

int print_hexa_upper(va_list types, char b[],
		int flags, int width, int _prec, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", b,
				flags, 'X', width, _prec, size));
}

/* PRINT HEXX NUM IN LOWER OR UPPER */

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @b: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @_prec: Precision specification
 * @size: Size specifier
 * @size: Size specification
 *
 * Return: Number of characters printed
 */

int print_hexa(va_list types, char map_to[], char b[],
		int flags, char flag_ch, int width, int _prec, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		b[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		b[i--] = flag_ch;
		b[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, b, flags, width, _prec, size));
}
