#include "utilities.h"

typedef struct s_strtol
{
	unsigned long	cutoff;
	int				cutlim;
	bool			clamped;
	char			*symbols;
	int				base;
	int				sign;
	int				val;
}	t_strtol;

static int	find_array_index(const char array[], int c)
{
	int	i;

	i = 0;
	while (array[i] != '\0')
	{
		if (array[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

static int	compute_prefix(const char **str, int *base, int *sign)
{
	if (!(*base >= 2 && *base <= 36) && *base != 0)
		return (EXIT_FAILURE);
	while (ft_isspace(**str))
		(*str)++;
	*sign = 1;
	if (**str == '-' && (*str)++)
		*sign = -1;
	else if (**str == '+')
		(*str)++;
	if (*base == 0 || *base == 16)
	{
		if (**str == '0' && (*(*str + 1) == 'X' || *(*str + 1) == 'x'))
		{
			if (*(*str + 2) == '\0')
				return (*base = 10, EXIT_SUCCESS);
			if (ft_strchr("0123456789ABCDEF", ft_toupper(*(*str + 2))) == NULL)
				return (*base = 10, EXIT_SUCCESS);
			return (*str += 2, *base = 16, EXIT_SUCCESS);
		}
		if (**str == '0')
			return (*base = 8, EXIT_SUCCESS);
		return (*base = 10, EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

static void	compute_cutoff(t_strtol *s)
{
	s->cutoff = LONG_MAX;
	if (s->sign == -1)
		s->cutoff = -(unsigned long)LONG_MIN;
	s->cutlim = s->cutoff % (unsigned long)s->base;
	s->cutoff /= (unsigned long)s->base;
}

static long	compute_long(const char **str, t_strtol *s)
{
	unsigned long	acc;

	acc = 0;
	while (**str != '\0')
	{
		s->val = find_array_index(s->symbols, ft_toupper(**str));
		if (s->val == -1)
			break ;
		(*str)++;
		if (s->clamped)
			continue ;
		if (acc > s->cutoff || (acc == s->cutoff && s->val > s->cutlim))
			s->clamped = true;
		acc *= s->base;
		acc += s->val;
	}
	if (s->clamped)
	{
		acc = (s->sign == -1) * LONG_MIN + (s->sign == 1) * LONG_MAX;
		errno = ERANGE;
	}
	else if (s->sign == -1)
		acc = -acc;
	return (acc);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long		num;
	t_strtol	s;

	s = (t_strtol){0};
	s.base = base;
	if (endptr != NULL)
		*endptr = (char *)str;
	if (compute_prefix(&str, &s.base, &s.sign) != EXIT_SUCCESS)
		return (errno = EINVAL, 0);
	s.symbols = ((char []){"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"});
	s.symbols[s.base] = '\0';
	if (*str == '\0' || ft_strchr(s.symbols, ft_toupper(*str)) == NULL)
		return (errno = EINVAL, 0);
	compute_cutoff(&s);
	num = compute_long(&str, &s);
	if (endptr != NULL)
		*endptr = (char *)str;
	return (num);
}
