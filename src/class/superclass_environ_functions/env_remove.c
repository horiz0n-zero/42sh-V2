/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 21:51:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/27 15:34:08 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool		env_cmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	if (*s1 == '=' || !*s1)
		return (true);
	return (false);
}

static size_t	env_remove_index(const char *key)
{
	extern char	**environ;
	size_t		index;

	index = 0;
	while (environ[index])
	{
		if (env_cmp(environ[index], key))
			return (index);
		index++;
	}
	return (42);
}

static void		env_move_rm(size_t index)
{
	extern char	**environ;

	index++;
	if (environ[index])
	{
		while (environ[index])
		{
			environ[index - 1] = environ[index];
			index++;
		}
		environ[index - 1] = NULL;
	}
}

int				env_remove(t_environ *const env, const char *key)
{
	size_t		index;
	size_t		count;
	extern char	**environ;

	if (!environ || !*environ)
		return (1);
	index = env_remove_index(key);
	if (index != 42)
	{
		count = env->count(0) - 1;
		free(environ[index]);
		environ[index] = NULL;
		env_move_rm(index);
	}
	else
		return (1);
	return (0);
}
