#include "utilities.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	pos;

	if (dst == NULL || src == NULL)
		return (NULL);
	pos = 0;
	while (pos < n)
	{
		((char *)dst)[pos] = ((char *)src)[pos];
		pos++;
	}
	return (dst);
}
