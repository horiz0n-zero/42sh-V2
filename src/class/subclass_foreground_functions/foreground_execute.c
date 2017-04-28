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

static int			foreground_argvs(t_dispatch *const dispatch, char **argvs)
{
	t_cmd 					*cmd;
	int 						status;

	status = 0;
	cmd = ((t_class*)dispatch->foreground->based_class_cmd)->ctor(
		dispatch->foreground->based_class_cmd, dispatch, argvs);
	if (cmd->is_ok)
		status = dispatch->foreground->execute(dispatch, cmd);
	else
		print("Command not found: %s\n", 1, *argvs);
	if (status)
		print("receive : %d\n", 1, status);
	return (status);
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
	if (foreground_argvs(dispatch, split))
		dispatch->display->prompt(dispatch, PR_FAILED);
	else
		dispatch->display->prompt(dispatch, PR_SUCCESS);
}
