#include "utilities.h"
#include <unistd.h>

int	ft_dwrite(int fd, const char *s)
{
	int	bytes;

	bytes = 0;
	while (*s != '\0')
		bytes += write(fd, s++, 1);
	return (bytes);
}
