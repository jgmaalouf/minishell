#include "format_output.h"

int	unsigned_length(unsigned long n, int radix, t_flags flags)
{
	int	prefix;
	int	zeros;
	int	digits;

	prefix = 0;
	if (flags.hash || flags.specifier == 'p')
		prefix = 2;
	digits = 0;
	if (n == 0 && flags.precision != 0)
		digits = 1;
	while (n)
	{
		n = n / radix;
		digits++;
	}
	zeros = 0;
	if (digits < flags.precision)
		zeros = flags.precision - digits;
	else if (flags.zero == '0' && (prefix + digits) < flags.width)
		zeros = flags.width - (prefix + digits);
	return (prefix + zeros + digits);
}

void	unsigned_padding(int zeros, t_flags flags, char *str)
{
	int	i;

	i = 0;
	while (zeros--)
		str[i++] = '0';
	if (flags.specifier == 'p')
		str[1] = 'x';
	else if (flags.hash)
	{
		if (flags.specifier == 'x')
			str[1] = 'x';
		if (flags.specifier == 'X')
			str[1] = 'X';
	}
}

char	*format_unsigned(unsigned long n, char *base, t_flags flags)
{
	char	*str;
	int		length;
	int		radix;

	radix = ft_strlen(base);
	length = unsigned_length(n, radix, flags);
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	unsigned_padding(length, flags, str);
	str[length--] = '\0';
	while (n)
	{
		str[length--] = base[n % radix];
		n = n / radix;
	}
	return (str);
}

void	fill_unsigned(unsigned long n, char *base, t_flags flags, char **output)
{
	int		length;
	char	*str;

	if (n == 0 || !(flags.specifier == 'x' || flags.specifier == 'X'))
		flags.hash = 0;
	if (flags.precision != -1)
		flags.zero = ' ';
	str = format_unsigned(n, base, flags);
	if (!str)
		return;
	length = ft_strlen(str);
	if (flags.minus)
		copy_str(str, length, output);
	if (flags.width && flags.zero == ' ')
		fill_width(flags.width, length, ' ', output);
	if (!flags.minus)
		copy_str(str, length, output);
	free((void *)str);
}
