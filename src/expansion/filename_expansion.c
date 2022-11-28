#include "minishell.h"

#include <glob.h>

// int	glob_pattern_match(const char *pattern, const char *filename)
int	glob_match(const char *pattern, const char *filename)
{
	if (!pattern || !filename)
		return (false);
	return (false);
}

int	ft_glob(const char *pattern, glob_t *pglob)
{
	DIR				*cwd;
	struct dirent	*cwd_data;
	// t_list			*filenames;
	int				i;

	i = 0;
	cwd = opendir(".");
	if (cwd == NULL)
		return (GLOB_ABORTED);
	cwd_data = readdir(cwd);
	while (cwd_data != NULL) // && !errno
	{
		pglob->gl_pathc++;
		if (glob_match(pattern, cwd_data->d_name))
		{
			pglob->gl_matchc++;
			pglob->gl_pathv[i++] = strdup(cwd_data->d_name);
			// ft_lstadd_back(&filenames, ft_lstnew(strdup(cwd_data->d_name)));
		}
		cwd_data = readdir(cwd);
	}
	// if (errno)
	// 	perror("readdir");
	closedir(cwd);
	// sort_filenames();
	return (EXIT_SUCCESS);
}

int	valid_glob_pattern(char *word)
{
	while (*word != '\0')
	{
		if (*word == '*' || *word == '?')
			return (true);
		if (*word == '\\')
			word += 2;
		else if (*word == '\'')
			word = find_closing_quote(word) + 1;
		else if (*word == '\"')
			word = find_closing_quote(word) + 1;
		else
			word++;
	}
	return (false);
}

t_token	*filename_expansion(t_token	*token)
{
	if (!valid_glob_pattern(token->val))
		return (token);
	printf("valid pattern:\n");
	// ft_glob(token->val, );
	return (NULL);
}
