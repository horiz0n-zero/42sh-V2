/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:57:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/27 20:17:53 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				foreground_argvs(t_dispatch *const dispatch, char **argvs)
{
	char			**argv;
	t_cmd			*cmd;

	argv = argvs;
	while (*argvs)
	{
		if (**argvs == ';')
		{
			*argvs = NULL;
		}
	}
}

void				foreground_exec(t_dispatch *const dispatch, char *buffer)
{
	char			**split;

	split = ft_strsplit(buffer, ft_isspace);
	if (!split || !*split)
	{
		if (split)
			free(split);
		dispatch->display->prompt(dispatch, PR_SUCCESS);
		return ;
	}
	foreground_argvs(dispatch, split);
}
