#include "main.h"

/**
 * get_precision - Extracts the precision value for printing
 * @format: The formatted string containing the format specifier
 * @i: Pointer to the index of the current character in the format string
 * @list: The list of arguments passed to _printf
 *
 * Return: The precision value if found, or -1 if not specified.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int precision = -1;

	if (format[curr_i] != '.')
		return (precision);

	precision = 0;

	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			/* Calculate the precision value from the format string */
			precision *= 10;
			precision += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			/* Retrieve precision from the argument list */
			curr_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (precision);
}
