#include "main.h"

/**
 * get_width - Calculates the width for printing
* @list: list of arguments.
 *
 * @format: Formatted string into which the arguments will be printed.
  *
  *
  * @i: List of arguments to be printed.
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curri_i;
	int width = 0;

	for (curri_i = *i + 1; format[curri_i] != '\0'; curri_i++)
	{
		if (is_digit(format[curri_i]))
		{
			width *= 10;
			width += format[curri_i] - '0';
		}
		else if (format[curri_i] == '*')
		{
			curri_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curri_i - 1;

	return (width);
}
