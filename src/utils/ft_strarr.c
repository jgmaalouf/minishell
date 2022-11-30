#include "utilities.h"

int	strarr_size(char *array[])
{
	int	size;

	size = 0;
	while (array[size] != NULL)
		size++;
	return (size);
}

char	**strarr_dup(char *array[])
{
	char	**result;
	int		size;
	int		i;

	size = strarr_size(array);
	result = malloc((size + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = strdup(array[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**strarr_resize(char *array[], int *size)
{
	char	**result;
	int		i;

	*size *= 2;
	result = calloc(*size, sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		result[i] = array[i];
		i++;
	}
	free(array);
	return (result);
}

void	strarr_free(char *array[])
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
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
