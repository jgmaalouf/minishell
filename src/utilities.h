#ifndef UTILITIES_H
# define UTILITIES_H

# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include "utils/libftprintf/libftprintf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	*ft_calloc(size_t count, size_t size);

int		ft_dwrite(int fd, const char *s);

char	*ft_concat(const char *s1, const char *s2);
char	*ft_concat3(const char *s1, const char *s2, const char *s3);

char	**dict_create(size_t *size);
void	*dict_destroy(char *dict[], size_t *size);
char	**dict_find_entry(char *dict[], const char *key);
char	*dict_get_val(char *dict[], const char *key);
char	**dict_set_val(char *dict[], const char *key, const char *val);
char	**dict_operation(int op);
char	**dict_close(void);
char	**dict_open(void);

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isnumber(char *s);
int		ft_isquote(int c);
int		ft_isspace(int c);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);

int		ft_setenv(const char *name, const char *value, int overwrite);

size_t	strarr_len(char *array[]);
char	**strarr_dup(char *array[]);
char	**strarr_resize(char *array[], size_t *size);
void	*strarr_free(char *array[]);
void	strarr_sort(char *array[]);

char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strsep(char **stringp, const char *delim);
char	*ft_strstr(const char *haystack, const char *needle);

long	ft_strtol(const char *str, char **endptr, int base);

int		ft_toupper(int c);

int		ft_unsetenv(const char *name);

#endif
