#include "format_output.h"

void	fill_width(int min_width, int content, char c, char **output)
{
	while (content < min_width)
	{
		**output = c;
		(*output)++;
		content++;
	}
}

void	fill_character(char c, t_flags flags, char **output)
{
	if (flags.minus)
	{
		**output = c;
		(*output)++;
	}
	if (flags.width)
		fill_width(flags.width, 1, flags.zero, output);
	if (!flags.minus)
	{
		**output = c;
		(*output)++;
	}
}

void	copy_str(char *str, int length, char **output)
{
	while (length-- > 0)
	{
		**output = *str;
		(*output)++;
		str++;
	}
	(*output)--;
}

void	fill_string(char *str, t_flags flags, char **output)
{
	int	length;

	if (!str)
		str = "(null)";
	length = ft_strlen(str);
	if (flags.precision >= 0 && length > flags.precision)
		length = flags.precision;
	if (flags.minus)
		copy_str(str, length, output);
	if (flags.width)
		fill_width(flags.width, length, flags.zero, output);
	if (!flags.minus)
		copy_str(str, length, output);
}
