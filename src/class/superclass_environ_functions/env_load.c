/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:38:47 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/13 22:12:04 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static const t_guard_struct	g_guard_required[] =
{
	{4, "TERM", guard_term},
	{4, "PATH", guard_path},
	{3, "PWD", guard_pwd},
	{5, "SHLVL", guard_shlvl},
	{1, "_", guard_underscore}
};

void						env_get_default(void)
{
	extern char				**environ;

	environ = malloc(sizeof(char*) *
			(sizeof(g_guard_required) / sizeof(g_guard_required[0]) + 1));
	if (!environ)
		return ;
	environ[0] = g_guard_required[0].get(g_guard_required[0]);
	environ[1] = g_guard_required[1].get(g_guard_required[1]);
	environ[2] = g_guard_required[2].get(g_guard_required[2]);
	environ[3] = g_guard_required[3].get(g_guard_required[3]);
	environ[4] = g_guard_required[4].get(g_guard_required[4]);
	environ[5] = NULL;
}

static int					env_compare(const char *ptr)
{
	size_t					len;
	int						index_guard;

	len = ft_strlen_magik(ptr, '=');
	index_guard = 0;
	while (index_guard < 7)
	{
		if (!ft_strncmp(ptr, g_guard_required[index_guard++].string, len))
			return (index_guard);
	}
	return (0);
}

size_t						env_count(void)
{
	extern char				**environ;
	char					**ptr;
	size_t					len;

	if (!environ || !*environ)
		return (0);
	len = 1;
	ptr = environ;
	while (*ptr++)
		len++;
	return (len);
}

static void					env_append_required(size_t index)
{
	char					*insert;
	extern char				**environ;
	char					**ptr;
	char					**new;

	insert = g_guard_required[index].get(g_guard_required[index]);
	new = malloc(sizeof(char*) * (env_count() + 1));
	ptr = new;
	index = (size_t)environ;
	if (!insert || !ptr || !new)
		return ;
	while (*environ)
	{
		*ptr++ = ft_strsub(*environ);
		free(*environ++);
	}
	*ptr++ = ft_strsub(insert);
	*ptr = NULL;
	free((void*)index);
	environ = new;
}
void						env_guard(void)
{
	extern char				**environ;
	char					**ptr;
	int						completed[env_count()];
	size_t					index;

	index = 0;
	ptr = environ;
	while (*ptr)
	{
		completed[index] = env_compare(*ptr++);
		index++;
	}
	while (index-- > 0)
	{
		if (completed[index])
			env_append_required(index);
	}
}
