/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:27:38 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/28 16:50:16 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static size_t	strlen_equal(const char *value)
{
	size_t		size;

	size = 0;
	if (value == NULL)
		return (0);
	while (value[size])
	{
		if (value[size] == '=')
			return (size);
		size++;
	}
	return (0);
}

static int		ft_envcmp(const char *value, const char *ptr)
{
	while (*value && *ptr)
	{
		if (*value != *ptr)
			break ;
		value++;
		ptr++;
	}
	if (*(value - 1) == '=' && *(ptr - 1) == '=')
		return (1);
	return (0);
}

static void		build_setenv_look(t_dispatch *const dispatch,
		const char *value)
{
	extern char	**environ;
	char		**ptr;
	size_t		size;

	size = strlen_equal(value);
	if (size == 0)
	{
		print("setenv : Bad argument %s\n", 1, value ? value : "(NULL)");
		return ;
	}
	ptr = environ;
	while (*ptr)
	{
		if (ft_envcmp(value, *ptr))
		{
			free(*ptr);
			*ptr = ft_strsub(value);
			return ;
		}
		ptr++;
	}
	dispatch->environ->append(dispatch->environ, value);
}

int				built_setenv(t_dispatch *const dispatch, char **argv)
{
	extern char **environ;

	argv++;
	if (argv && *argv)
	{
		while (*argv)
			build_setenv_look(dispatch, *argv++);
		dispatch->environ->sort(dispatch->environ->count(0), environ,
								dispatch->environ->sort_type);
	}
	else
		print("\e[36msetenv \e[32m: remove all $VAR specified\n\e[37m", 0);
	dispatch->hashtable->refresh(dispatch);
	return (0);
}
