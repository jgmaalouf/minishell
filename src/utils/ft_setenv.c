#include "utilities.h"
/*
static char	**find_env_name(const char *name)
{
	extern char	**environ;
	char		**eptr;
	size_t		namelen;

	eptr = environ;
	namelen = ft_strlen(name);
	while (*eptr != NULL)
	{
		if (strncmp(*eptr, name, namelen) == 0 && (*eptr)[namelen] == '=')
			return (eptr);
		eptr++;
	}
	return (eptr);
}
 */
static void	add_to_end(size_t index, const char *name, const char *value)
{
	extern char	**environ;

	environ[index] = ft_concat3(name, "=", value);
	environ[index + 1] = NULL;
}

static void	change_value(size_t index, const char *name, const char *value)
{
	extern char	**environ;

	free(environ[index]);
	environ[index] = ft_concat3(name, "=", value);
}

static int	add_to_environ(const char *name, const char *value, int overwrite)
{
	extern char		**environ;
	static size_t	size;
	size_t			index;

	if (size == 0 && environ != NULL)
		size = strarr_len(environ) + 1;
	/* index = find_env_name(name) - environ; */
	index = dict_find_entry(environ, name) - environ;
	if (environ[index] == NULL)
	{
		if (index + 1 == size)
		{
			environ = strarr_resize(environ, &size);
			if (environ == NULL)
				return (-1);
		}
		add_to_end(index, name, value);
	}
	else if (overwrite == 1)
		change_value(index, name, value);
	return (EXIT_SUCCESS);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
		return (-1);
	return (add_to_environ(name, value, overwrite));
}
