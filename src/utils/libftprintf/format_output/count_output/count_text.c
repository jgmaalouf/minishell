#include "format_output.h"

int	count_width(int min_width, int content)
{
	int	count;

	count = 0;
	while (content < min_width)
	{
		count++;
		content++;
	}
	return (count);
}

int	count_character(t_flags flags)
{
	int	count;

	count = 0;
	if (flags.minus || !flags.minus)
		count++;
	if (flags.width)
		count += count_width(flags.width, 1);
	return (count);
}

int	count_string(char *str, t_flags flags)
{
	int	count;
	int	length;

	if (!str)
		str = "(null)";
	length = ft_strlen(str);
	if (flags.precision >= 0 && length > flags.precision)
		length = flags.precision;
	count = 0;
	if (flags.minus)
		count += length;
	if (flags.width)
		count += count_width(flags.width, length);
	if (!flags.minus)
		count += length;
	return (count);
}
