#include "format_output.h"

int	count_unsigned(unsigned long n, char *base, t_flags flags)
{
	int		count;
	int		length;
	char	*str;

	if (n == 0 || !(flags.specifier == 'x' || flags.specifier == 'X'))
		flags.hash = 0;
	if (flags.precision != -1)
		flags.zero = ' ';
	str = format_unsigned(n, base, flags);
	if (!str)
		return (0);
	length = ft_strlen(str);
	count = 0;
	if (flags.minus || !flags.minus)
		count += length;
	if (flags.width && flags.zero == ' ')
		count += count_width(flags.width, length);
	free((void *)str);
	return (count);
}
