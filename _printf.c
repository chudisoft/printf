#include <stdarg.h>
#include "main.h"

/**
 * _printf - writes formated characters to stdout
 * @format: The character to print
 *
 * Return: count of the printed string.
 */
int _printf(const char *format, ...)
{
	va_list arg;
	char *val;
	int counter = 0, formatLength, i = 0;

	va_start(arg, format);
	formatLength = _strlen(format);

	for (i = 0; i < formatLength; i++)
	{
		if (format[i] == '%')
		{
			switch (format[i + 1])
			{
				case 'c':
					_putchar(va_arg(arg, int));
					counter++;
					break;
				case 's':
					counter += _printS(va_arg(arg, char *));
					break;
				case '%':
					_putchar('%');
					counter++;
					break;
			}
			i++;
		}
		else
		{
			_putchar((int)format[i]);
			counter++;
		}
	}

	va_end(arg);
	return (counter);
}
