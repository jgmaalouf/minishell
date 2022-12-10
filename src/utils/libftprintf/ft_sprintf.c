#include "libftprintf.h"

int	ft_sprintf(char * restrict str, const char * restrict format, ...)
{
	int		nbyte;
	va_list	ap;

	va_start(ap, format);
	nbyte = ft_vsprintf(str, format, ap);
	va_end(ap);
	return (nbyte);
}
