#include "utilities.h"

int	ft_isnumber(char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	while (ft_isdigit(*s++))
		if (*s == '\0')
			return (true);
	return (false);
}
