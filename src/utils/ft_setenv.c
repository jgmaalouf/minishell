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
		if (strncmp(*ep, name, namelen) == 0 && (*ep)[namelen] == '=')
			return (ep);
		ep++;
	}
	return (ep);
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

/*
char **debug;
static int	add_to_environ(const char *name, const char *value, int overwrite)
{
	extern char		**environ; debug = environ;
	static size_t	size;
	size_t			index;

	printf("ft_setenv %p\n", environ);

	if (size == 0)
		size = strarr_len(environ) + 1;
	// index = find_env_name(name) - environ;
	index = dict_find_entry(environ, name) - environ;
	if (strarr_len(environ) + 2 >= size)
		environ = strarr_resize(environ, &size);
	debug = environ;
	if (environ[index] == NULL)
	{
		if (index + 2 >= size)
		// if (index + 2 >= size)
		{
			environ = strarr_resize(environ, &size);
			printf("resize %p\n", environ);
			if (environ == NULL)
				return (errno = ENOMEM, -1);
			debug = environ;
		}
		add_to_end(index, name, value);
	}
	else if (overwrite == 1)
		change_value(index, name, value);
	return (EXIT_SUCCESS);
}
 */

/*
static int	add_to_environ(const char *name, const char *value, int overwrite)
{
	extern char	**environ;
	static char	**last_environ;
	char		**ep;
	size_t		len;

	const size_t namelen = strlen(name);
	ep = environ;
	len = 0;
	if (ep != NULL)
	{
		while (*ep != NULL)
		{
			len++;
			if (strncmp(*ep, name, namelen) == 0 && (*ep)[namelen] == '=')
				break;
			ep++;
		}
	}
	if (ep == NULL)
	{
		char **new_environ;
	}
}
 */

char **debug;
static int	add_to_environ(const char *name, const char *value, int overwrite)
{
	extern char		**environ; debug = environ;
	static char		**last_environ;
	size_t			index;
	size_t			len;

	// printf("ft_setenv %p\n", environ);
	if (environ != last_environ)
		free(last_environ);
	index = dict_find_entry(environ, name) - environ;
	len = index + 1;
	if (environ[index] == NULL)
	{
		environ = strarr_resize(environ, &len);
		if (environ == NULL)
			return (errno = ENOMEM, -1);
		add_to_end(index, name, value);
	}
	else if (overwrite == 1)
		change_value(index, name, value);
	last_environ = environ;
	return (EXIT_SUCCESS);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
		return (errno = EINVAL, -1);
	return (add_to_environ(name, value, overwrite));
}
