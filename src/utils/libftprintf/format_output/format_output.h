#ifndef FORMAT_OUTPUT_H
# define FORMAT_OUTPUT_H

# define DECIMAL "0123456789"
# define UPRHEXA "0123456789ABCDEF"
# define LWRHEXA "0123456789abcdef"
# define SPECIFIERS "cspdiuxX%"

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_flags
{
	int	hash;
	int	space;
	int	plus;
	int	minus;
	int	zero;
	int	width;
	int	precision;
	int	specifier;
}	t_flags;

char	*format_output(const char * restrict format, va_list ap);
int		count_format(const char **format, va_list *args);
void	fill_format(const char ** format, char **output, va_list *ap_cpy);
t_flags	get_flags(const char **format, va_list *ap_cpy);

/* Count ***************************************/
int		count_width(int min_width, int content);
int		count_character(char c, t_flags flags);
int		count_string(char *str, t_flags flags);
int		count_signed(long n, char *base, t_flags flags);
int		count_unsigned(unsigned long n, char *base, t_flags flags);

/* Fill ***************************************/
void	copy_str(char *str, int length, char **output);
void	fill_width(int min_width, int content, char c, char **output);
void	fill_character(char c, t_flags flags, char **output);
void	fill_string(char *str, t_flags flags, char **output);
void	fill_signed(long n, char *base, t_flags flags, char **output);
void	fill_unsigned(unsigned long n, char *base, t_flags flags, char **output);

int		unsigned_length(unsigned long n, int radix, t_flags flags);
void	unsigned_padding(int zeros, t_flags flags, char *str);
char	*format_unsigned(unsigned long n, char *base, t_flags flags);

int		signed_length(long n, int radix, t_flags flags);
void	signed_padding(long n, int zeros, t_flags flags, char *str);
char	*format_signed(long n, char *base, t_flags flags);

int		ft_isdigit(int c);
int		ft_strlen(const char *s);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);

#endif