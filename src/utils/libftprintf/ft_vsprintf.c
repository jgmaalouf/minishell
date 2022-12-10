#include "libftprintf.h"

int	ft_vsprintf(char * restrict str, const char * restrict format, va_list ap)
{
	int		nbyte;
	char	*output;

	output = format_output(format, ap);
	if (output == NULL)
		return (-1);
	nbyte = ft_strlen(output);
	ft_memcpy(str, output, nbyte + 1);
	return (free(output), nbyte);
}
