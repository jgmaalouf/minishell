#include "utilities.h"

static char	**find_env_name(const char *name)
{
	extern char	**environ;
	char		**eptr;
	size_t		namelen;

	eptr = environ;
	namelen = ft_strlen(name);
	while (*eptr != NULL)
	{
		if (strncmp(*eptr, name, namelen) == 0 && ((*eptr)[namelen] == '=' || (*eptr)[namelen] == '\0'))
			return (eptr);
		eptr++;
	}
	return (eptr);
}

static void	add_to_end(int pos, const char *name, const char *value)
{
	extern char	**environ;

	if (value == NULL)
		environ[pos] = strdup(name);
	else
		environ[pos] = ft_concat3(name, "=", value);
	environ[pos + 1] = NULL;
}

static void	change_value(int pos, const char *name, const char *value)
{
	extern char	**environ;

	free(environ[pos]);
	if (value == NULL)
		environ[pos] = strdup(name);
	else
		environ[pos] = ft_concat3(name, "=", value);
}

static int	add_to_environ(const char *name, const char *value, int overwrite)
{
	extern char	**environ;
	static int	size;
	int			pos;

	if (size == 0)
		size = strarr_size(environ) + 1;
	pos = find_env_name(name) - environ;
	if (environ[pos] == NULL)
	{
		if (pos + 1 >= size)
		{
			environ = strarr_resize(environ, &size);
			if (environ == NULL)
				return (-1);
		}
		add_to_end(pos, name, value);
	}
	else if (overwrite == 1)
		change_value(pos, name, value);
	return (EXIT_SUCCESS);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
		return (-1);
	return (add_to_environ(name, value, overwrite));
}
