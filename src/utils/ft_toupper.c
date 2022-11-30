#include "utilities.h"

int	ft_toupper(int c)
{
	return (c - (c >= 'a' && c <= 'z') * ('a' - 'A'));
}
