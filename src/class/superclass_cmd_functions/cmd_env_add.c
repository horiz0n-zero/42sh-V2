#include "shell.h"

static char					*ft_value(const char *key)
{
	extern char				**environ;
	char					**ptr;
	const char				*save;
	char					*env;

	save = key;
	ptr = environ;
	if (!ptr)
		return (NULL);
	while (*ptr)
	{
		env = *ptr++;
		while (*env && *key)
		{
			if (*env != *key)
				break ;
			env++;
			key++;
		}
		key = save;
		if (*env != '=')
			continue ;
		else
			return (++env);
	}
	return (NULL);
}

static void 	env_push_dollar(char **string)
{
	char 		*path;

	if (*(*string + 1) == '0' && !*(*string + 2))
		*string = "-minishell";
	else if (!*(*string + 1))
		*string = "$";
	else
	{
		path = ft_value(*string + 1);
		if (path)
			*string = path;
		else
			*string = "";
	}
}

void			cmd_env(t_cmd *const cmd, char **argv)
{
	(void)cmd;
	while (*argv)
	{
		if (**argv == '$')
			env_push_dollar(argv);
		argv++;
	}
}
