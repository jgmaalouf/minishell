#include "utilities.h"

int	ft_isnumber(char *s)
{
	while (*s != '\0')
		if (!ft_isdigit(*s++))
			return (false);
	return (true);
}
