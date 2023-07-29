#include "main.h"

/**
 * get_flags - Extracts active formatting flags from the format specifier
 * @format: The formatted string containing the format specifier
 * @i: Pointer to the index of the current character in the format string
 *
 * Return: Flags indicating active formatting options.
 */
int get_flags(const char *format, int *i)
{
	/* Flags characters: - + 0 # ' ' */
	/* Corresponding bit positions: 1 2 4 8  16  */
	int j, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
		{
			if (format[curr_i] == FLAGS_CH[j])
			{
				/* Set the corresponding flag bit in the flags variable */
				flags |= FLAGS_ARR[j];
				break;
			}
		}

		/* Stop when no more valid flags are found */
		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}
