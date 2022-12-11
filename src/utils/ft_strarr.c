#include "utilities.h"

size_t	strarr_len(char *array[])
{
	size_t	len;

	len = 0;
	while (array[len] != NULL)
		len++;
	return (len);
}

char	**strarr_dup(char *array[])
{
	char	**result;
	int		len;
	int		i;

	len = strarr_len(array);
	result = malloc((len + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = ft_strdup(array[i]);
		if (result[i] == NULL)
			return (strarr_free(array));
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**strarr_resize(char *array[], size_t *size)
{
	char	**result;

	*size = strarr_len(array) + 1;
	result = ft_calloc(*size + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	ft_memcpy((char *)result, (char *)array, *size * sizeof(char *));
	return (free(array), result);
}

void	*strarr_free(char *array[])
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	return (free(array), NULL);
}

void	strarr_sort(char *array[])
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (array[i] != NULL)
	{
		j = i + 1;
		while (array[j] != NULL)
		{
			if (ft_strcmp(array[j], array[i]) < 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
