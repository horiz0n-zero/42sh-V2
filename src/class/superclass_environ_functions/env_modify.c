/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:32:22 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/27 15:32:25 by afeuerst         ###   ########.fr       */
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

int				env_modify(const char *key, const char *value)
{
	size_t		index;
	extern char	**environ;
	char		*new;

	if (!environ || !key || !value)
		return (1);
	index = env_remove_index(key);
	if (index == 42)
		return (1);
	free(environ[index]);
	new = malloc(sizeof(char) * (LENS(key) + LENS(value) + 2));
	if (!new)
		return (1);
	environ[index] = ft_strincjoin(key, value, '=', new);
	return (0);
}
