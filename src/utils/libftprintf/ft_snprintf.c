#include "libftprintf.h"

int	ft_snprintf(char *restrict str, size_t size,
		const char *restrict format, ...)
{
	int		nbyte;
	va_list	ap;

	va_start(ap, format);
	nbyte = ft_vsnprintf(str, size, format, ap);
	va_end(ap);
	return (nbyte);
}
