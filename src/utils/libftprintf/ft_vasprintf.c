#include "libftprintf.h"

int	ft_vasprintf(char **ret, const char *format, va_list ap)
{
	int	nbyte;

	/* dynamically allocate output */
	*ret = format_output(format, ap);
	if (*ret == NULL)
		return (-1);
	nbyte = ft_strlen(*ret);
	return (nbyte);
}
