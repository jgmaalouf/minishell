#include "libftprintf.h"

int	ft_asprintf(char **ret, const char *format, ...)
{
	int		nbyte;
	va_list	ap;

	va_start(ap, format);
	nbyte = ft_vasprintf(ret, format, ap);
	va_end(ap);
	return (nbyte);
}
