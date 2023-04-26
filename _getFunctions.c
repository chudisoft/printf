#include "main.h"

/**
 * fetchFlags - Computes active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter
 *
 * Return: flags
 */
int fetchFlags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8 16 */

	int j, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH,
		F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[curr_i] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}
		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}

/**
 * fetchPreci - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments
 *
 * Return: Precision
 */

int fetchPreci(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int _prec = -1;

	if (format[curr_i] != '.')
		return (_prec);

	_prec = 0;

	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (_hasDigit(format[curr_i]))
		{
			_prec *= 10;
			_prec += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			_prec = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (_prec);
}

/**
 * fetchSize - Computes the size to cast the argument
 * @format: Formatted string in which to print the arguments
 *  @i: List of arguments to be printed.
 *
 *  Return: Precision.
 */

int fetchSize(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = S_LONG;
	else if (format[curr_i] == 'h')
		size = S_SHORT;
	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;
	return (size);
}

/**
 * fetchWidth - Calculates the width for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed
 * @list: list of arguments
 *
 * Return: width
 */

int fetchWidth(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (_hasDigit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (width);
}

