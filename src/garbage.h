#ifndef GARBAGE_H
# define GARBAGE_H

/* malloc exit(EXIT_FAILURE) */

/* PROHIBITED */
#include <ctype.h>
#include <string.h>
/* PROHIBITED */



# define DELIMITERS "\"'$ =@(*)#:/"
# define WORDCHARS  ""    // '*?_-.[]~&;!#$%^(){}<>' WORDCHARS='~!#$%^&*(){}[]<>?.+;-'

# define ASCII_DELIMITERS "\t\n\v\f\r !\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~"



typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

t_env	*preprocess_environment(char **envp);
void	free_env(t_env *env);



#endif
