#include "minishell.h"
#include <glob.h>

static int	ft_glob(const char *pattern, glob_t *pglob)
{
	DIR				*cwd;
	struct dirent	*cwd_data;
	t_pat			*groups;

	errno = 0;
	cwd = opendir(".");
	if (cwd == NULL)
		return (GLOB_ABORTED);
	groups = group_subpatterns(pattern);
	cwd_data = readdir(cwd);
	while (cwd_data != NULL && ++(pglob->gl_pathc))
	{
		if (globbing(groups, cwd_data->d_name))
			pglob->gl_pathv[pglob->gl_pathc++] = ft_strdup(cwd_data->d_name);
		cwd_data = readdir(cwd);
	}
	free_pattern_groups(groups);
	if (errno)
		perror("readdir");
	closedir(cwd);
	if (pglob->gl_pathc == 0)
		return (GLOB_NOMATCH);
	strarr_sort(pglob->gl_pathv);
	return (EXIT_SUCCESS);
}

static size_t	count_directory_entries(const char *directory)
{
	size_t			count;
	DIR				*cwd;
	struct dirent	*cwd_data;

	errno = 0;
	cwd = opendir(directory);
	if (cwd == NULL)
		return (0);
	count = 0;
	cwd_data = readdir(cwd);
	while (cwd_data != NULL && ++count)
		cwd_data = readdir(cwd);
	if (errno)
		perror("readdir");
	closedir(cwd);
	return (count);
}

static int	init_glob_struct(glob_t	*pglob)
{
	size_t	max;

	max = count_directory_entries(".");
	if (max == 0)
		return (EXIT_FAILURE);
	*pglob = (glob_t){0};
	pglob->gl_pathv = ft_calloc(max + 1, sizeof(char *));
	if (pglob->gl_pathv == NULL)
		return (GLOB_NOSPACE);
	return (EXIT_SUCCESS);
}

t_token	*filename_expansion(t_token	*token)
{
	glob_t	pglob;
	t_token	*next;
	t_token	*new;
	int		i;

	if (init_glob_struct(&pglob) != EXIT_SUCCESS)
		return (token);
	if (ft_glob(token->val, &pglob) != EXIT_SUCCESS)
		return (strarr_free(pglob.gl_pathv), token);
	free(token->val);
	next = token->next;
	token->next = NULL;
	i = 0;
	token->val = pglob.gl_pathv[i++];
	token->expanded = true;
	while (pglob.gl_pathv[i] != NULL)
	{
		new = new_token_node(TK_WORD, pglob.gl_pathv[i++]);
		new->expanded = true;
		tokenlist_add_back(&token, new);
	}
	free(pglob.gl_pathv);
	return (tokenlist_add_back(&token, next), token);
}
