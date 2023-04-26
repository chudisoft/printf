#include "main.h"

/*PRINT CHAR*/

/**
 * _printC - Prints a character
 * @types: Arguments lists
 * @b: Array of buffer to handle print
 * @flags: Calculates active flags
 * @width: Array width.
 * @_prec: Specification for precision
 * @size: Specifier for size
 *
 * Return: Numbers of char printed.
 */
int _printC(va_list types, char b[],
		int flags, int width, int _prec, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, b, flags, width, _prec, size));
}

/* PRINT A STRING */

/**
 * _printS - Prints string
 * @types: Arguments lists
 * @b: Array of buffer to handle print
 * @flags: Calculates active flags
 * @width: Array width.
 * @_prec: Specification for precision
 * @size: Specifier for size
 *
 * Return: Numbers of char printed.
 */

int _printS(va_list types, char b[],
		int flags, int width, int _prec, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(b);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(_prec);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (_prec >= 6)
			str = " ";
	}

	while (str[length] != '\0')
		length++;

	if (_prec >= 0 && _prec < length)
		length = _prec;

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

	return (write(1, str, length));
}

/* PRINT PERCENT */

/**
 * _printPerc - Prints percent
 * @types: Arguments lists
 * @b: Array of buffer to handle print
 * @flags: Calculates active flags
 * @width: Array width.
 * @_prec: Specification for precision
 * @size: Specifier for size
 *
 * Return: Numbers of char printed.
 */

int _printPerc(va_list types, char b[],
		int flags, int width, int _prec, int size)
{
	UNUSED(types);
	UNUSED(b);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(_prec);
	UNUSED(size);

	return (write(1, "%%", 1));
}


/* PRINT INT */

/**
 * _printI - Print int
 * @types: Arguments lists
 * @b: Array of buffer to handle print
 * @flags: Calculates active flags
 * @width: Array width.
 * @_prec: Specification for precision
 * @size: Specifier for size
 *
 * Return: Numbers of char printed.
 */

int _printI(va_list types, char b[],
		int flags, int width, int _prec, int size)
{
	int has_neg = 0;
	int i = BUFF_SIZE - 2;
	unsigned long int num;
	long int n = va_arg(types, long int);

	n = size_to_number(n, size);

	if (n == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		has_neg = 1;
	}

	while (num > 0)
	{
		b[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(has_neg, i, b, flags, width, _prec, size));
}

/* PRINT BINARY */

/**
 * _printB - Prints out unsigned numbers
 * @types: Arguments lists
 * @b: Array of buffer to handle print
 * @flags: Calculates active flags
 * @width: Array width.
 * @_prec: Specification for precision
 * @size: Specifier for size
 *
 * Return: Numbers of char printed.
 */

int _printB(va_list types, char b[],
		int flags, int width, int _prec, int size)
{
	unsigned int arr[32];
	unsigned int i, total, k, l;
	int c;

	UNUSED(b);
	UNUSED(_prec);
	UNUSED(width);
	UNUSED(size);
	UNUSED(flags);

	k = va_arg(types, unsigned int);
	l = 2147483648;
	arr[0] = k / l;
	for (i = 1; i < 32; i++)
	{
		l /= 2;
		arr[i] = (k / l) % 2;
	}
	for (i = 0, total = 0, c = 0; i < 32; i++)
	{
		total += arr[i];
		if (total || i == 31)
		{
			char z = '0' + arr[i];

			write(1, &z, 1);
			c++;
		}
	}
	return (c);
}
