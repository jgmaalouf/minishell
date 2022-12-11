#include "utilities.h"
/*
static char	**find_env_name(const char *name)
{
	extern char	**environ;
	char		**ep;
	size_t		namelen;

	ep = environ;
	namelen = ft_strlen(name);
	while (*ep != NULL)
	{
		if (ft_strncmp(*ep, name, namelen) == 0 && (*ep)[namelen] == '=')
			return (ep);
		ep++;
	}
	return (ep);
}
 */

static int	add_to_environ(const char *name, const char *value, int overwrite)
{
	char	**ep;
	size_t	index;
	size_t	len;

	ep = ft_environ(ENVIRON_GET, NULL);
	index = dict_find_entry(ep, name) - ep;
	len = index + 1;
	if (ep[index] == NULL)
	{
		ep = strarr_resize(ep, &len);
		if (ep == NULL)
			return (errno = ENOMEM, -1);
		ep[index] = ft_concat3(name, "=", value);
		ep[index + 1] = NULL;
	}
	else if (overwrite == 1)
	{
		free(ep[index]);
		ep[index] = ft_concat3(name, "=", value);
	}
	ft_environ(ENVIRON_SAVE, ep);
	return (EXIT_SUCCESS);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
		return (errno = EINVAL, -1);
	return (add_to_environ(name, value, overwrite));
}
