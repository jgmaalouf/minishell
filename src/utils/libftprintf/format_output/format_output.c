#include "format_output.h"

int	count_output(const char *format, va_list ap)
{
	int		total;
	int		count;
	va_list	ap_cpy;

	if (!format)
		return (0);
	va_copy(ap_cpy, ap);
	total = 0;
	while (*format)
	{
		if (*format != '%')
			total++;
		else
		{
			format++;
			count = count_format(&format, &ap_cpy);
			if (count < 0)
				return (0);
			total += count;
		}
		format++;
	}
	va_end(ap_cpy);
	return (total);
}

void	fill_output(const char *format, va_list ap, char *output)
{
	va_list	ap_cpy;

	va_copy(ap_cpy, ap);
	while (*format != '\0')
	{
		if (*format != '%')
			*output = *format;
		else
		{
			format++;
			fill_format(&format, &output, &ap_cpy);
		}
		format++;
		output++;
	}
	va_end(ap_cpy);
}

char	*format_output(const char *restrict format, va_list ap)
{
	int		count;
	char	*output;

	count = count_output(format, ap);
	if (count == 0)
		return (NULL);
	output = ft_calloc(count + 1, sizeof(char));
	if (output != NULL)
		fill_output(format, ap, output);
	return (output);
}
