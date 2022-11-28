#include "utilities.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1);
	ret = malloc(len + 1);
	if (ret != NULL)
		ft_memcpy(ret, s1, len + 1);
	return (ret);
}
