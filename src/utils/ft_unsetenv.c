#include "utilities.h"

static void	delete_from_environ(char **ep)
{
	free(*ep);
	ep[0] = ep[1];
	while (*(++ep) != NULL)
		ep[0] = ep[1];
}

int	ft_unsetenv(const char *name)
{
	extern char	**environ;
	char		**ep;
	size_t		namelen;

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
		return (errno = EINVAL, -1);
	namelen = ft_strlen(name);
	ep = environ;
	if (ep != NULL)
	{
		while (*ep != NULL)
		{
			if (ft_strncmp(*ep, name, namelen) == 0 && (*ep)[namelen] == '=')
				delete_from_environ(ep);
			else
				ep++;
		}
	}
	return (EXIT_SUCCESS);
}
