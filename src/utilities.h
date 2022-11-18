#ifndef UTILITIES_H
# define UTILITIES_H

# include <stdlib.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char*	ft_concat(const char *s1, const char *s2);

int		ft_isdigit(int c);
int		ft_isnumber(char *s);
int		ft_isquote(char c);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));

void	*ft_memcpy(void *dst, const void *src, size_t n);

char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strsep(char **stringp, const char *delim);

#endif
