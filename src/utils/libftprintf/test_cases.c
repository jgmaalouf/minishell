#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	char	*str1 = "fst_string";
	char	*str2 = "snd_string";
	char	*str3 = "trd_string";

	printf("%3$s, %2$s, %1$s\n", str1, str2, str3);
	printf("START%sEND\n", str1);
	// printf("%3$s, %s\n", str1, str2, str3);
	// printf("%2$s, %s\n", str1, str2, str3);
	int	len = 3;
	printf("%.*s\n", len, str1);
	int	width = 30;
	printf("%*s\n", width, str1);
	return (0);
}
