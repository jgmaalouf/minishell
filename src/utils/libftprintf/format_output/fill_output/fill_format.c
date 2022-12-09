#include "../format_output.h"

void	fill_format(const char ** format, char **output, va_list *ap_cpy)
{
	t_flags	flags;

	flags = get_flags(format, ap_cpy);
	if (flags.specifier == 'c')
		fill_character(va_arg(*ap_cpy, int), flags, output);
	else if (flags.specifier == 's')
		fill_string(va_arg(*ap_cpy, char *), flags, output);
	else if (flags.specifier == 'd' || flags.specifier == 'i')
		fill_signed(va_arg(*ap_cpy, int), DECIMAL, flags, output);
	else if (flags.specifier == 'u')
		fill_unsigned(va_arg(*ap_cpy, unsigned), DECIMAL, flags, output);
	else if (flags.specifier == 'p')
		fill_unsigned(va_arg(*ap_cpy, unsigned long), LWRHEXA, flags, output);
	else if (flags.specifier == 'x')
		fill_unsigned(va_arg(*ap_cpy, unsigned), LWRHEXA, flags, output);
	else if (flags.specifier == 'X')
		fill_unsigned(va_arg(*ap_cpy, unsigned), UPRHEXA, flags, output);
	else if (flags.specifier == '%')
		fill_character('%', flags, output);
}
