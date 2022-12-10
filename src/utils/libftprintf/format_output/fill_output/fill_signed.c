#include "format_output.h"

int	signed_length(long n, int radix, t_flags flags)
{
	int	sign;
	int	zeros;
	int	digits;

	sign = 0;
	if (n < 0 || flags.plus || flags.space)
		sign = 1;
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
	else if (flags.zero == '0' && (sign + digits) < flags.width)
		zeros = flags.width - (sign + digits);
	return (sign + zeros + digits);
}

void	signed_padding(long n, int zeros, t_flags flags, char *str)
{
	int	i;

	i = 0;
	while (zeros--)
		str[i++] = '0';
	if (n < 0)
		*str = '-';
	else if (flags.plus)
		*str = '+';
	else if (flags.space)
		*str = ' ';
}

char	*format_signed(long n, char *base, t_flags flags)
{
	char	*str;
	int		length;
	int		radix;

	radix = ft_strlen(base);
	length = signed_length(n, radix, flags);
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	signed_padding(n, length, flags, str);
	str[length--] = '\0';
	if (n < 0)
		n *= -1;
	while (n)
	{
		str[length--] = base[n % radix];
		n = n / radix;
	}
	return (str);
}

void	fill_signed(long n, char *base, t_flags flags, char **output)
{
	int		length;
	char	*str;

	if (flags.precision != -1)
		flags.zero = ' ';
	str = format_signed(n, base, flags);
	if (!str)
		return ;
	length = ft_strlen(str);
	if (flags.minus)
		copy_str(str, length, output);
	if (flags.width && flags.zero == ' ')
		fill_width(flags.width, length, ' ', output);
	if (!flags.minus)
		copy_str(str, length, output);
	free((void *)str);
}
