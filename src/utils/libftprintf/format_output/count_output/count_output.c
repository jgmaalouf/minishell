#include "../format_output.h"

int	count_format(const char **format, va_list *ap_cpy)
{
	t_flags	flags;

	flags = get_flags(format, ap_cpy);
	if (flags.specifier == 'c')
		return (count_character(va_arg(*ap_cpy, int), flags));
	if (flags.specifier == 's')
		return (count_string(va_arg(*ap_cpy, char *), flags));
	if (flags.specifier == 'd' || flags.specifier == 'i')
		return (count_signed(va_arg(*ap_cpy, int), DECIMAL, flags));
	if (flags.specifier == 'u')
		return (count_unsigned(va_arg(*ap_cpy, unsigned), DECIMAL, flags));
	if (flags.specifier == 'p')
		return (count_unsigned(va_arg(*ap_cpy, unsigned long), LWRHEXA, flags));
	if (flags.specifier == 'x')
		return (count_unsigned(va_arg(*ap_cpy, unsigned), LWRHEXA, flags));
	if (flags.specifier == 'X')
		return (count_unsigned(va_arg(*ap_cpy, unsigned), UPRHEXA, flags));
	if (flags.specifier == '%')
		return (count_character('%', flags));
	return (-1);
}
