#include "utilities.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (p != NULL)
		ft_memset(p, 0, (count * size));
	return (p);
}
