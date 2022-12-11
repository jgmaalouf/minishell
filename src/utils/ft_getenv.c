#include "utilities.h"

char	*ft_getenv(const char *name)
{
	char	**ep;
	size_t	namelen;

	ep = ft_environ(ENVIRON_GET, NULL);
	if (ep == NULL || name[0] == '\0')
		return (NULL);
	namelen = ft_strlen(name);
	while (*ep != NULL)
	{
		if (ft_strncmp(*ep, name, namelen) == 0 && (*ep)[namelen] == '=')
			return (*ep + namelen + 1);
		ep++;
	}
	return (NULL);
}
