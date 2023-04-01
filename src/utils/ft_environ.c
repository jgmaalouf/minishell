#include "utilities.h"

char	**ft_environ(int action, char **new_environ)
{
	static char	**last_environ;

	if (action == ENVIRON_SAVE)
	{
		last_environ = new_environ;
		return (new_environ);
	}
	if (action == ENVIRON_GET)
		return (last_environ);
	if (action == ENVIRON_DESTROY)
		strarr_free(last_environ);
	return (errno = EINVAL, NULL);
}
