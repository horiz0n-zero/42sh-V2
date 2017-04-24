/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_execute_simple.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:57:33 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/24 19:50:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		 		foreground_execute(t_dispatch *const dispatch, t_cmd *const cmd)
{
	pid_t	 	child;
	int			status;
	extern char **environ;

	status = 0;
	if (cmd->is_ok == false || !cmd->argv)
	{
		if (cmd->argv && *cmd->argv)
			print("Command not found: %s\n", 1, *cmd->argv);
		else
			print("Bad arguments\n", 0);
		return (0);
	}
	if (cmd->is_builtin)
			return (cmd->is_builtin(dispatch, cmd->argv));
	child = fork();
	if (!child)
		execve(*cmd->argv, cmd->argv, environ);
	else
		waitpid(child, &status, 0);
	return (status);
}
