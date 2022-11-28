#include "utilities.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ret;

	if (ft_strlen(s1) <= n)
		return (ft_strdup(s1));
	ret = malloc(n + 1);
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, s1, n);
	ret[n] = '\0';
	return (ret);
}
