#include "format_output.h"

t_flags	init_flags(void)
{
	t_flags	flags;

	flags.hash = 0;
	flags.space = 0;
	flags.plus = 0;
	flags.minus = 0;
	flags.zero = ' ';
	flags.width = 0;
	flags.precision = -1;
	flags.specifier = 0;
	return (flags);
}

int	get_width(const char **format, va_list *ap_cpy)
{
	int	width;

	if (**format == '*')
	{
		width = va_arg(*ap_cpy, int);
		if (width < 0)
			width *= -1;
	}
	else
	{
		// width = ft_atoi(*format);
		width = ft_strtol(*format, NULL, 10);
		while (ft_isdigit(*(*format + 1)))
			(*format)++;
	}
	return (width);
}

int	get_precision(const char **format, va_list *ap_cpy)
{
	int	precision;

	if (*(*format + 1) == '*')
	{
		(*format)++;
		precision = va_arg(*ap_cpy, int);
	}
	else
	{
		if (!ft_isdigit(*(*format + 1)))
			return (0);
		(*format)++;
		// precision = ft_atoi(*format);
		precision = ft_strtol(*format, NULL, 10);
		while (ft_isdigit(*(*format + 1)))
			(*format)++;
	}
	return (precision);
}

t_flags	get_flags(const char **format, va_list *ap_cpy)
{
	t_flags	flags;

	flags = init_flags();
	while (!ft_strchr("cspdiuxX%", **format))
	{
		if (**format == '#')
			flags.hash = 1;
		if (**format == ' ')
			flags.space = 1;
		if (**format == '+')
			flags.plus = 1;
		if (**format == '-')
			flags.minus = 1;
		if (**format == '0')
			flags.zero = '0';
		if ((**format >= '1' && **format <= '9') || **format == '*')
			flags.width = get_width(format, ap_cpy);
		if (**format == '.')
			flags.precision = get_precision(format, ap_cpy);
		(*format)++;
	}
	flags.specifier = **format;
	if (flags.minus)
		flags.zero = ' ';
	return (flags);
}
