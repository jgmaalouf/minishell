#include "utilities.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*dst;

	dst = malloc(sizeof(t_list));
	if (dst == NULL)
		return (NULL);
	dst->content = content;
	dst->next = NULL;
	return (dst);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == NULL)
		return ;
	if (*lst != NULL)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (*lst != NULL)
	{
		ft_lstclear((&(*lst)->next), del);
		(*del)((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}
