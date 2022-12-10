#include "format_output.h"

int	count_signed(long n, char *base, t_flags flags)
{
	int		count;
	int		length;
	char	*str;

	if (flags.precision != -1)
		flags.zero = ' ';
	str = format_signed(n, base, flags);
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
