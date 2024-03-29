#include "utilities.h"

char	*ft_concat(const char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	return (result);
}

char	*ft_concat3(const char *s1, const char *s2, const char *s3)
{
	char	*result;
	char	*concat;

	concat = ft_concat(s1, s2);
	if (concat == NULL)
		return (NULL);
	result = ft_concat(concat, s3);
	free(concat);
	return (result);
}
