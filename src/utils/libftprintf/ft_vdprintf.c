#include "libftprintf.h"

int	ft_vdprintf(int fd, const char * restrict format, va_list ap)
{
	int		nbyte;
	char	*output;

	/* dynamically allocate output */
	output = format_output(format, ap);
	if (output == NULL)
		return (-1);
	nbyte = write(fd, output, ft_strlen(output));
	return (free(output), nbyte);
}
