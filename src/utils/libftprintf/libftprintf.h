#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "format_output.h"

int	ft_asprintf(char **ret, const char *format, ...);
int	ft_dprintf(int fd, const char *restrict format, ...);
int	ft_printf(const char *restrict format, ...);
int	ft_snprintf(char *restrict str, size_t size,
		const char *restrict format, ...);
int	ft_sprintf(char *restrict str, const char *restrict format, ...);
int	ft_vasprintf(char **ret, const char *format, va_list ap);
int	ft_vdprintf(int fd, const char *restrict format, va_list ap);
int	ft_vprintf(const char *restrict format, va_list ap);
int	ft_vsnprintf(char *restrict str, size_t size,
		const char *restrict format, va_list ap);
int	ft_vsprintf(char *restrict str, const char *restrict format, va_list ap);

#endif
