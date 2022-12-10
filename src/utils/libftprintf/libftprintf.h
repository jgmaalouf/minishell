#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "format_output.h"

int	ft_vdprintf(int fd, const char * restrict format, va_list ap);
int	ft_dprintf(int fd, const char * restrict format, ...);
int	ft_vprintf(const char * restrict format, va_list ap);
int	ft_vasprintf(char **ret, const char *format, va_list ap);
int	ft_printf(const char * restrict format, ...);
int	ft_asprintf(char **ret, const char *format, ...);

#endif
