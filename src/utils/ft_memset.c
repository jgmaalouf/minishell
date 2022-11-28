#include "utilities.h"

void	*ft_memset(void *b, int c, size_t len)
{
	register char	*b_str;

	b_str = (char *)b;
	while (len--)
		*b_str++ = (unsigned char)c;
	return (b);
}
