#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

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

char*	ft_concat(const char *s1, const char *s2)
{
	char	*result;
	int		len1;
	int		len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	return (result);
}
