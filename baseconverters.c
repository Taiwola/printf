#include "main.h"

unsigned int convert_sbase(buffer_t *output, long int num, char *base,
				unsigned char flags, int w, int p);
unsigned int convert_ubase(buffer_t *output,
				unsigned long int num, char *base,
				unsigned char flags, int w, int p);

/**
 * convert_sbase - convert a signed long into an input base
 * @output: A buffer_t struct
 * @num: long to be converted
 * @base: pointer
 * @flags: flags
 * @w: width
 * @p: precision modifier
 * Return:the number of bytes stored
 */

unsigned int convert_sbase(buffer_t *output, long int num, char *base, 
		unsigned char flags, int w, int p);
{
	int size;
	char digit, pad = '0';
	unsigned int ret = 1;

	for (size = 0; *(base + size);)
		size++;

	if (num >= size || num <= -size)
		ret += convert_sbase(output, num / size, base,
				flags, wid - 1, prec - 1);
	else
	{
		for (; p > 1; p--, w--)
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0)
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; w > 1; w--)
				ret += _memcpy(output, &pad, 1);
		}
	}
	digit = base[(num < 0 ? -1 : 1) * (num % size)];
	_memcpy(output, &digit, 1);

	return (ret);
}

/**
 * convert_ubase - converts unsigned long into an input base
 * @output: A buffer_t struct
 * @num: An unsigned long to be converted
 * @base: A pointer to a string containing the base to convert to
 * @flags: Flag
 * @w: width
 * @p: precision modifier
 * Return: number of bytes stored
 */

unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int w, int p)
{
	unsigned int size, ret = 1;
	char digit, pad = '0', *lead = "0x";

	for (size = 0; *(base + size);)
		size++;

	if (num >= size)
		ret += convert_ubase(output, num / size, base,
				flags, w - 1, p - 1);
	else
	{
		if (((flags >> 5) & 1) == 1)
		{
			w -= 2;
			p -= 2;
		}
		for (; prec > 1; p--, w--)
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0)
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; w > 1; w--)
				ret += _memcpy(output, &pad, 1);
		}
		if (((flags >> 5) & 1) == 1)
			ret += _memcpy(output, lead, 2);
	}

	digit = base[(num % size)];
	_memcpy(output, &digit, 1);

	return (ret);
}
