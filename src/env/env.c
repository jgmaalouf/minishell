#include "minishell.h"

/* t_env	*new_env_node(char *key, char *val) */
t_env	*new_env_node(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = NULL;
	new->val = NULL;
	new->next = NULL;
	return (new);
}

/*
void	env_list_add_back(t_env **list, t_env *new)
{
	t_env	*tmp;

	if (list == NULL)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}
 */

/* extern char	**environ; */
t_env	*preprocess_environment(char **envp)
{
	t_env	*env;
	t_env	*ptr;
	int	i;

	env = new_env_node();
	ptr = env;
	i = 0;
	while (envp[i] != NULL)
	{
		// array = ft_str_split(envp[i++], "=");
		ptr->key = strsep(&envp[i], "=");
		ptr->val = strsep(&envp[i], "=");
		if (envp[i + 1] != NULL)
			ptr->next = new_env_node();
		ptr = ptr->next;
		i++;
	}
	return (env);
}
