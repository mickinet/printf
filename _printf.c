#include "main.h"
void print_buffer(char buffer[], int *buff_inde);

/**
 * _printf - Function that selects the correct function to print.
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int p, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_inde = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (p = 0; format && format[p] != '\0'; p++)
	{
		if (format[p] != '%')
		{
			buffer[buff_ind++] = format[p];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[p], 1); */
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_inde);
			flags = get_flags(format, &p);
			width = get_width(format, &p, list);
			precision = get_precision(format, &p, list);
			size = get_size(format, &p);
			++p;
			printed = handle_print(format, &p, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_inde);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - If the buffer exists, it prints the content
 * @buff_inde: Index at which to add next char, it represents the length.
 * @buffer: An array of chars.
 */
void print_buffer(char buffer[], int *buff_inde)
{
	if (*buff_inde > 0)
		write(1, &buffer[0], *buff_inde);

	*buff_inde = 0;
}
