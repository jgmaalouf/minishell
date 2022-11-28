#include "utilities.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	needle_length;

	if (*needle == '\0')
		return ((char *)haystack);
	needle_length = ft_strlen(needle);
	while (*haystack != '\0')
	{
		if (ft_strncmp(haystack, needle, needle_length) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
