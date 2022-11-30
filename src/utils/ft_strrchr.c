#include "utilities.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*chr;

	chr = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			chr = (char *)s;
		s++;
	}
	if (c == '\0')
		chr = (char *)s;
	return (chr);
}
