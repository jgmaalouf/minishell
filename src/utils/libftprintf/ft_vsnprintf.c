#include "libftprintf.h"

int	ft_vsnprintf(char * restrict str, size_t size, const char * restrict format, va_list ap)
{
	int		nbyte;
	char	*output;
	size_t	len;

	output = format_output(format, ap);
	if (output == NULL)
		return (-1);
	len = ft_strlen(output);
	if (len + 1 <= size)
		ft_memcpy(str, output, len + 1);
	else
	{
		ft_memcpy(str, output, size - 1);
		str[size] = '\0';
	}
	nbyte = ft_strlen(output);
	return (free(output), nbyte);
}
