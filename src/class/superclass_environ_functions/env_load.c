/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:38:47 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 11:54:40 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static const t_guard_struct		g_guard_required[] =
{
	{4, "TERM", guard_term},
	{4, "PATH", guard_path},
	{3, "PWD", guard_pwd},
	{5, "SHLVL", guard_shlvl},
	{1, "_", guard_underscore}
};

static size_t					iskeyofvalue(const char *key)
{
	size_t						index;
	const char					*ptr;
	const char					*cmp;

	index = 0;
	while (index < GUARD_COUNT)
	{
		ptr = key;
		cmp = g_guard_required[index].string;
		while (*ptr)
		{
			if (*ptr != *cmp || !*cmp)
				return (0);
			else if (*cmp == '=')
				return (index);
			cmp++;
			ptr++;
		}
		index++;
	}
	return (0);
}

void							env_guard(t_environ *const env)
{
	extern char					**environ;
	char						**environ_ptr;
	size_t						index;
	int							board[GUARD_COUNT];
	size_t						key;

	index = 0;
	environ_ptr = environ;
	if (!environ_ptr)
		return ;
	while (*environ_ptr)
	{
		if ((key = iskeyofvalue(*environ_ptr)))
			board[key] = 42;
		environ_ptr++;
	}
	while (index < GUARD_COUNT)
	{
		if (board[index] == 42)
			env->append(env,
					g_guard_required[index].get(g_guard_required[index]));
		index++;
	}
}

void							env_get_default(t_environ *const env)
{
	extern char					**environ;
	size_t						index;

	index = 0;
	environ = malloc(sizeof(char*) *
			((sizeof(g_guard_required) / sizeof(g_guard_required[0]))
			+ 1 + ENV_SPACE_AVAILABLE));
	if (!environ)
		return ;
	while (index < GUARD_COUNT)
	{
		environ[index] = g_guard_required[index].get(g_guard_required[index]);
		index++;
	}
	env->size = GUARD_COUNT + ENV_SPACE_AVAILABLE;
}
