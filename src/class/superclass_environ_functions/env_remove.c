/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 21:51:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/13 22:04:47 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static void		stc_remove(const size_t index)
{
	extern char	**environ;
	char		**ptr;
	char		**new;
	size_t		index_env;

	index_env = 0;
	new = malloc(sizeof(char*) * env_count() - 1);
	ptr = new;
	if (!new)
		return ;
	while (environ[index_env])
	{
		if (index_env == index)
		{
			free(environ[index_env++]);
			continue ;
		}
		*ptr++ = ft_strsub(environ[index_env]);
		free(environ[index_env++]);
	}
	free(environ);
	environ = new;
}

int				env_remove(const char *key)
{
	extern char	**environ;
	size_t		index;
	size_t		len;

	len = ft_strlen_s(key);
	index = 0;
	if (!environ || !*environ)
		return (1);
	while (environ[index])
	{
		if (!ft_strncmp(key, environ[index], len))
		{
			stc_remove(index);
			return (0);
		}
		index++;
	}
	return (1);
}
