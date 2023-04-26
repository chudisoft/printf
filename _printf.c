#include "main.h"

void handle_buffer(char b[], int *bIndex);

/**
 * _printf - prints formated string to standard output
 * @format: formated string containing the string to print with specifiers
 * Return: count of Printed characters
 */
int _printf(const char *format, ...)
{
	int j, fExpCount = 0, printCount = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char b[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (j = 0; format && format[j] != '\0'; j++)
	{
		if (format[j] != '%')
		{
			b[buff_ind++] = format[j];
			if (buff_ind == BUFF_SIZE)
				handle_buffer(b, &buff_ind);
			/* write(1, &format[i], 1); */
			printCount++;
		}
		else
		{
			handle_buffer(b, &buff_ind);
			flags = fetchFlags(format, &j);
			width = fetchWidth(format, &j, list);
			precision = fetchPreci(format, &j, list);
			size = fetchSize(format, &j);
			++j;
			fExpCount = _processPrint(format, &j, list, b,
					flags, width, precision, size);
			if (fExpCount == -1)
				return (-1);
			printCount += fExpCount;
		}
	}

	handle_buffer(b, &buff_ind);

	va_end(list);

	return (printCount);
}

/**
 * handle_buffer - handles buffer contents if they exists
 * @b:  Character arrays
 * @bIndex: Index to add next character, representing the length.
 */

void handle_buffer(char b[], int *bIndex)
{
	if (*bIndex > 0)
		write(1, &b[0], *bIndex);

	*bIndex = 0;
}
