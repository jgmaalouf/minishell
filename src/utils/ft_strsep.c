#include "utilities.h"

char	*ft_strsep(char **stringp, const char *delim)
{
	char	*ret;

	if (*stringp == NULL)
		return (NULL);
	ret = *stringp;
	while (**stringp != '\0')
	{
		if (ft_strchr(delim, **stringp))
			break ;
		(*stringp)++;
	}
	if (**stringp == '\0')
		*stringp = NULL;
	else
		*(*stringp)++ = '\0';
	return (ret);
}

/*
int	main (void)
{
	const char *delim = ".W";
	char *string1 = strdup("Hello, World, ...");
	char *string2 = strdup("Hello, World, ...");
	char *result1, *result2;

	printf("i: %s\n\n", string1);

	result1 = strsep(&string1, delim);
	printf("o: %s\n", string1); printf("r: %s\n", result1);
	result2 = ft_strsep(&string2, delim);
	printf("o: %s\n", string2); printf("r: %s\n", result2);

	printf("\n");
	if (string1)
		printf("diff (string): %d\n", strcmp(string1, string2));
	if (result1)
		printf("diff (result): %d\n", strcmp(result1, result2));
	return (EXIT_SUCCESS);
}
 */
