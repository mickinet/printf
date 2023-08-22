#include "main.h"
/****************** Print Pointer******/
/**
 * print_pointer - Prints the value that’s in a pointer variable.
 * @types: List a of arguments,
 * @buffer: Buffer array to handle print,
 * @flags:  Calculates active flags,
* @size: Size specifier.
 * @precision: Precision specification.
* @width: get the width.
  * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/******  PRINT NON Printable ***********/
/**
 * print_non_printable - Print ascii codes in hexadeci of non printable chars.
* @buffer: Buffer array to handle print
 * @types: Lista of arguments
* @flags:  Calculates active flags
   * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int g = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[g] != '\0')
	{
		if (is_printable(str[g]))
			buffer[g + offset] = str[g];
		else
			offset += append_hexa_code(str[g], buffer, g + offset);

		g++;
	}

	buffer[g + offset] = '\0';

	return (write(1, buffer, g + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @buffer: Buffer array to handle all prints.
 * @flags:  Calculates active flags
 * @width: get width
 * @types: List of arguments.
 * @precision: Specification of the precision.
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int o, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (o = 0; str[o]; o++)
		;

	for (o = o - 1; o >= 0; o--)
	{
		char z = str[o];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/********************** Print A String In ROT13 ***********************/
/**
 * print_rot13string - Print a string in rot13.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
* @types: List of arguments
 * @flags:  Calculates all active flags.
* @size: Size specifier
 * @width: get width,
 * @precision: Precision specification.
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int e, r;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (e = 0; str[e]; e++)
	{
		for (r = 0; in[r]; r++)
		{
			if (in[r] == str[e])
			{
				x = out[r];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[r])
		{
			x = str[e];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
