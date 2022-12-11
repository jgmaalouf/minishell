#include "libftprintf.h"

int	ft_vprintf(const char *restrict format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}
