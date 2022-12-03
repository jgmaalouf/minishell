#include "utilities.h"
#define DICTSIZE 4

char	**dict_create(size_t *size)
{
	char	**dict;

	*size = DICTSIZE;
	dict = calloc(*size, sizeof(char *));
	if (dict == NULL)
		exit(EXIT_FAILURE);
	return (dict);
}

void	*dict_destroy(char *dict[], size_t *size)
{
	int	i;

	i = 0;
	while (dict[i] != NULL)
		free(dict[i++]);
	free(dict);
	*size = 0;
	return (NULL);
}

char	**dict_find_entry(char *dict[], const char *key)
{
	char	**entry;
	size_t	keylen;

	entry = dict;
	keylen = strlen(key);
	while (*entry != NULL)
	{
		if (strncmp(*entry, key, keylen) == 0 && (*entry)[keylen] == '=')
			return (entry);
		entry++;
	}
	return (entry);
}

char	*dict_get_val(char *dict[], const char *key)
{
	char	**entry;

	entry = dict_find_entry(dict, key);
	if (*entry == NULL)
		return (NULL);
	return (strchr(*entry, '=') + 1);
}

char	**dict_set_val(char *dict[], const char *key, const char *val)
{
	char	**entry;

	entry = dict_find_entry(dict, key);
	if (*entry != NULL)
		free(*entry);
	*entry = ft_concat3(key, "=", val);
	return (entry);
}

/* char	**dict_access(int op) */
char	**dict_operation(int op)
{
	static char		**dict;
	static size_t	size;

	if (op == 0)
	{
		if (dict != NULL)
			dict = dict_destroy(dict, &size);
		return (NULL);
	}
	if (op == 1)
	{
		if (dict == NULL)
			dict = dict_create(&size);
		else if (strarr_len(dict) + 1 == size)
			dict = strarr_resize(dict, &size);
		return (dict);
	}
	return (NULL);
}

char	**dict_close(void)
{
	return (dict_operation(0));
}

char	**dict_open(void)
{
	return (dict_operation(1));
}

// --------------------------------------------------------------
/*
#include <stdio.h>

static void	print_dictionary(char *dict[])
{
	for (size_t i = 0; dict[i] != NULL; i++)
		printf("%s\n", dict[i]);
	printf("\n");
}

static void	function1(void)
{
	char	**dict = NULL;

	dict = dict_open();
	print_dictionary(dict);
	dict_set_val(dict, "first", "1st");
}

static void	function2(void)
{
	char	**dict = NULL;

	dict = dict_open();
	print_dictionary(dict);
	dict_set_val(dict, "second", "2nd");
}

static void	function3(void)
{
	char	**dict = NULL;

	dict = dict_open();
	print_dictionary(dict);
	dict_set_val(dict, "third", "3rd");
}

int	main(int argc, char *argv[])
{
	char	**dict;

	function1();
	function2();
	function3();
	dict = dict_open();
	print_dictionary(dict);
	dict_close();
	return (0);
}
 */
