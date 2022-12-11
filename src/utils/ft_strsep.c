#include "utilities.h"

char	*ft_strsep(char **stringp, const char *delim)
{
	char	*ret;

	if (*stringp == NULL)
		return (NULL);
	ret = *stringp;
	while (**stringp != '\0')
	{
		if (ft_strchr(delim, **stringp))
			break ;
		(*stringp)++;
	}
	if (**stringp == '\0')
		*stringp = NULL;
	else
		*(*stringp)++ = '\0';
	return (ret);
}
