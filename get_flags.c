#include "main.h"

/**
 * get_flags - Calculates the active flags.
 * @i: take a parameter.
 * @format: Formatted string in which to print the arguments
 *
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int f, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (f = 0; FLAGS_CH[f] != '\0'; f++)
			if (format[curr_i] == FLAGS_CH[f])
			{
				flags |= FLAGS_ARR[f];
				break;
			}

		if (FLAGS_CH[f] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}
