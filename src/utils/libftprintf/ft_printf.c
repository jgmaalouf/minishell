#include "libftprintf.h"

int	ft_printf(const char * restrict format, ...)
{
	int		nbyte;
	va_list	ap;

	va_start(ap, format);
	nbyte = ft_vprintf(format, ap);
	va_end(ap);
	return (nbyte);
}
