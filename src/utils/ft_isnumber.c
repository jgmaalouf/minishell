#include "utilities.h"

int	ft_isnumber(char *s)
{
	if (s == NULL)
		return (false);
	while (*s != '\0')
		if (!ft_isdigit(*s++))
			return (false);
	return (true);
}
