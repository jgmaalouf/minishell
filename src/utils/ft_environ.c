#include "utilities.h"

char	**ft_environ(int action, char **new_environ)
{
	static char	**last_environ;

	if (action == ENVIRON_SAVE)
	{
		if (last_environ == new_environ)
			return (new_environ);
		last_environ = new_environ;
		return (new_environ);
	}
	if (action == ENVIRON_GET)
		return (last_environ);
	if (action == ENVIRON_DESTROY)
		strarr_free(last_environ);
	return (NULL);
}
