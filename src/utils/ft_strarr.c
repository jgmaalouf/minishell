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
		result[i] = strdup(array[i]);
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
	// int		i;

	*size = strarr_len(array) + 1;
	// *size *= 2;
	result = calloc(*size + 2, sizeof(char *));
	if (result == NULL)
		return (NULL);
	// i = -1;
	// while (array[++i] != NULL)
	// 	ft_memcpy(&result[i], &array[i], sizeof(char *));
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
			if (strcmp(array[j], array[i]) < 0)
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
