#include "main.h"

/**
 * _processPrint - Handles printing based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @list: Arguments List to be printed.
 * @ind: index.
 * @b: Array buffer to handle print.
 * @flags: Calculates active flags
 * @width: gets width.
 * @_prec: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int _processPrint(const char *fmt, int *ind, va_list list, char b[],
		int flags, int width, int _prec, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', _printC}, {'s', _printS}, {'%', _printPerc},
		{'i', _printI}, {'d', _printI}, {'b', _printB},
		{'u', _printU}, {'o', _printO}, {'x', _printH},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, b, flags, width, _prec, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
