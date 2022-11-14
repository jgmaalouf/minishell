#include "minishell.h"

#include <glob.h>

// int	glob_pattern_match(char const *pattern, char const *filename)
int	glob_match(char const *pattern, char const *filename)
{
	if (strcmp(pattern, "*") == 0 && *filename != '.')
		return (true);
	if (strcmp(pattern, ".*") == 0 && *filename == '.')
		return (true);
	while (*pattern != '\0' && *filename != '\0')
	{
		if (*pattern != '*' && *pattern != '?')
		{
			if (*(filename++) != *(pattern++))
				return (false);
		}
		if (*pattern == '*' && pattern++)
			filename = strchr(filename, *pattern);
		if (*pattern == '?' && pattern++)
			filename++;
	}
	if (*filename == '\0' && *pattern == '\0')
		return (true);
	return (false);
}

int	ft_glob(char const *pattern, glob_t *pglob)
{
	DIR				*cwd;
	struct dirent	*cwd_data;
	t_list			*filenames;
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
	return (false);
}

t_token	*filename_expansion(t_token	*token)
{
	if (!valid_glob_pattern(token->val))
		return (token);
	// ft_glob(token->val, );
	return (NULL);
}
