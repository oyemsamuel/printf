#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a single character
 * @types: List of arguments containing the character to be printed
 * @buffer: Buffer array to handle printing
 * @flags: Active formatting flags
 * @width: Width of the output
 * @precision: Precision value
 * @size: Size specification
 *
 * Return: Number of characters printed.
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List of arguments containing the string to be printed
 * @buffer: Buffer array to handle printing
 * @flags: Active formatting flags
 * @width: Width of the output
 * @precision: Precision value
 * @size: Size specification
 *
 * Return: Number of characters printed.
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

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

/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: List of arguments (not used in this function)
 * @buffer: Buffer array to handle printing
 * @flags: Active formatting flags (not used in this function)
 * @width: Width of the output (not used in this function)
 * @precision: Precision value (not used in this function)
 * @size: Size specification (not used in this function)
 *
 * Return: Number of characters printed (always 1).
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print an integer
 * @types: List of arguments containing the integer to be printed
 * @buffer: Buffer array to handle printing
 * @flags: Active formatting flags
 * @width: Width of the output
 * @precision: Precision value
 * @size: Size specification
 *
 * Return: Number of characters printed.
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number in binary format
 * @types: List of arguments containing the number to be printed
 * @buffer: Buffer array to handle printing
 * @flags: Active formatting flags (not used in this function)
 * @width: Width of the output (not used in this function)
 * @precision: Precision value (not used in this function)
 * @size: Size specification (not used in this function)
 *
 * Return: Number of characters printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
