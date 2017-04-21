/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 19:32:10 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 17:24:09 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_hashb	g_hash_builtins[] =
{
	{built_env, "env"},
	{built_unsetenv, "unsetenv"},
	{built_setenv, "setenv"},
	{built_cd, "cd"},
	{built_echo, "echo"},
	{built_exit, "exit"},
	{built_exit, "quit"},
	{NULL, NULL}
};

static bool				compare(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (false);
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (false);
	return (true);
}

static void				ft_lookfor(t_dispatch *const dispatch, char **split)
{
	const t_hashb		*array = (const t_hashb*)&g_hash_builtins;

	while (array->built)
	{
		if (compare(array->text, *split))
		{
			return ;
			array->built(dispatch);
		}
		array++;
	}
}

void					ft_start(t_dispatch *const dispatch)
{
	char				**split;
	void				*wfree;
	char				*found;

	split = ft_strsplit(dispatch->display->buffer, ft_isspace);
	if (split == NULL || *split == NULL)
		return ;
	wfree = split;
	found = dispatch->hashtable->get(dispatch->hashtable, *split);
	if (found == NULL)
		ft_lookfor(dispatch, split);
	else
	{
		print("found : %P %s \n", 2, found, found);
	}
	dispatch->display->prompt(dispatch, PR_SUCCESS);
	free(split);
}
