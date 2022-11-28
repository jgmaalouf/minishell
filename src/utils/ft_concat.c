#include "utilities.h"

char	*ft_concat(const char *s1, const char *s2)
{
	char	*result;
	int		len1;
	int		len2;

	// if (s1 == NULL || s2 == NULL)
	// 	return (NULL);
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

	// if (s1 == NULL || s2 == NULL || s3 == NULL)
	// 	return (NULL);
	concat = ft_concat(s1, s2);
	result = ft_concat(concat, s3);
	free(concat);
	return (result);
}
