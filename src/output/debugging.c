#include "minishell.h"

void	debugging_log_print_env(t_env *env)
{
	while (env->next != NULL)
	{
		printf(BLU "key: " NOC "%s, ", env->key);
		printf(GRN "val: " NOC "%s  ", env->val);
		printf("\n");
		env = env->next;
	}
}
