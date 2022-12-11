#include "libftprintf.h"

int	ft_dprintf(int fd, const char *restrict format, ...)
{
	int		nbyte;
	va_list	ap;

	va_start(ap, format);
	nbyte = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (nbyte);
}
