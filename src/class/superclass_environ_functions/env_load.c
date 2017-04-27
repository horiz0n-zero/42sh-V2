/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:38:47 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/27 19:31:13 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_guard_struct		g_guard_required[] =
{
	{4, "TERM", guard_term},
	{4, "PATH", guard_path},
	{3, "PWD", guard_pwd},
	{6, "OLDPWD", guard_pwd},
	{5, "SHLVL", guard_shlvl},
	{1, "_", guard_underscore},
	{4, "HOME", guard_home},
	{8, "CLICOLOR", guard_lscolor}
};

static int						iskeyofvalue(const char *key)
{
	int							index;
	const char					*ptr_key;
	const char					*guard_string;

	index = 0;
	while (index < GUARD_COUNT)
	{
		guard_string = g_guard_required[index].string;
		ptr_key = key;
		while (*guard_string && *ptr_key)
		{
			if (*guard_string != *ptr_key)
				break ;
			guard_string++;
			ptr_key++;
			if (*ptr_key == '=' && !*guard_string)
				return (index);
		}
		index++;
	}
	return (-1);
}

void							env_guard(t_environ *const env)
{
	extern char					**environ;
	char						**ptr;
	int							index;
	int							board[GUARD_COUNT];

	if (!(ptr = environ))
	{
		env_get_default(env);
		return ;
	}
	while (*ptr)
	{
		if ((index = iskeyofvalue(*ptr)) != -1)
			board[index] = 42;
		ptr++;
	}
	index = 0;
	while (index < GUARD_COUNT)
	{
		if (board[index] != 42)
			env->append(env,
					g_guard_required[index].get(g_guard_required[index]));
		index++;
	}
}

void							env_kill(void)
{
	extern char					**environ;
	char						**ptr;

	ptr = environ;
	if (!ptr)
		return ;
	while (*ptr)
	{
		free(*ptr);
		*ptr++ = NULL;
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
	environ[index] = NULL;
	env->size = GUARD_COUNT + ENV_SPACE_AVAILABLE;
}
