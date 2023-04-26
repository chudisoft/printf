#include "main.h"

/* WRITE HANDLE */
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @b: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @_preci: precision specifier
 * @size: Size specifier
 *
 * Return: Written chars count.
 */
int handle_write_char(char c, char b[],
	int flags, int width, int _preci, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(_preci);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	b[i++] = c;
	b[i] = '\0';

	if (width > 1)
	{
		b[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			b[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &b[0], 1) +
					write(1, &b[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &b[BUFF_SIZE - i - 1], width - 1) +
					write(1, &b[0], 1));
	}

	return (write(1, &b[0], 1));
}

/* WRITE NUMBER */
/**
 * write_number - Prints a string
 * @has_negative: Lista of arguments
 * @ind: char types.
 * @b: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @_preci: precision specifier
 * @size: Size specifier
 *
 * Return: Written chars count.
 */
int write_number(int has_negative, int ind, char b[],
	int flags, int width, int _preci, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (has_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, b, flags, width, _preci,
		length, padd, extra_ch));
}

/**
 * write_num - Prints a number using a bufffer
 * @ind: Index of buffer
 * @b: Buffer
 * @flags: Flags
 * @width: width
 * @_prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Written chars count
 */
int write_num(int ind, char b[],
	int flags, int width, int _prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (_prec == 0 && ind == BUFF_SIZE - 2 && b[ind] == '0' && width == 0)
		return (0);
	if (_prec == 0 && ind == BUFF_SIZE - 2 && b[ind] == '0')
		b[ind] = padd = ' ';
	if (_prec > 0 && _prec < length)
		padd = ' ';
	while (_prec > length)
		b[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			b[i] = padd;
		b[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				b[--ind] = extra_c;
			return (write(1, &b[ind], length) + write(1, &b[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				b[--ind] = extra_c;
			return (write(1, &b[1], i - 1) + write(1, &b[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				b[--padd_start] = extra_c;
			return (write(1, &b[padd_start], i - padd_start) +
				write(1, &b[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		b[--ind] = extra_c;
	return (write(1, &b[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @has_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @b: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @_preci: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int has_negative, int ind,
	char b[],
	int flags, int width, int _preci, int size)
{
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(has_negative);
	UNUSED(size);

	if (_preci == 0 && ind == BUFF_SIZE - 2 && b[ind] == '0')
		return (0);

	if (_preci > 0 && _preci < length)
		padd = ' ';

	while (_preci > length)
	{
		b[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			b[i] = padd;

		b[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &b[ind], length) + write(1, &b[0], i));
		}
		else
		{
			return (write(1, &b[0], i) + write(1, &b[ind], length));
		}
	}

	return (write(1, &b[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @b: Arrays of chars
 * @ind: Index of buffer
 * @length: Number Length
 * @width: Specifier's Width
 * @flags: Specifier's Flags
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Written chars count.
 */
int write_pointer(char b[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			b[i] = padd;
		b[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			b[--ind] = 'x';
			b[--ind] = '0';
			if (extra_c)
				b[--ind] = extra_c;
			return (write(1, &b[ind], length) + write(1, &b[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			b[--ind] = 'x';
			b[--ind] = '0';
			if (extra_c)
				b[--ind] = extra_c;
			return (write(1, &b[3], i - 3) + write(1, &b[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				b[--padd_start] = extra_c;
			b[1] = '0';
			b[2] = 'x';
			return (write(1, &b[padd_start], i - padd_start) +
				write(1, &b[ind], length - (1 - padd_start) - 2));
		}
	}
	b[--ind] = 'x';
	b[--ind] = '0';
	if (extra_c)
		b[--ind] = extra_c;
	return (write(1, &b[ind], BUFF_SIZE - ind - 1));
}
