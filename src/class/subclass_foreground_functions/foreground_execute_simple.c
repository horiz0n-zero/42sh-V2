/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_execute_simple.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:57:33 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/26 18:23:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int 			ft_foreground_status(t_cmd *const cmd)
{
	if (cmd->argv && *cmd->argv)
		print("Command not found : %s\n", 1, *cmd->argv);
	else
		print("Bad arguments\n", 0);
	return (42);
}

static void 		execute(t_cmd *const cmd)
{
	pid_t 			shell;
	pid_t 			shell_gp;
	extern char 	**environ;

	shell = getpid();
	shell_gp = getpgrp();
	if (!shell_gp)
		shell_gp = shell;
	setpgid(shell, shell_gp);
	if (!cmd->background)
		tcsetpgrp(STDIN_FILENO, shell_gp);
	ft_default_signal();
	if (cmd->stdin != STDIN_FILENO)
	{
		close(STDIN_FILENO);
		dup2(cmd->stdin, STDIN_FILENO);
	}
	if (cmd->stdout != STDOUT_FILENO)
	{
		close(STDOUT_FILENO);
		dup2(cmd->stdout, STDOUT_FILENO);
	}
	if (cmd->stderr != STDERR_FILENO)
	{
		close(STDERR_FILENO);
		dup2(cmd->stderr, STDERR_FILENO);
	}
	execve(*cmd->argv, cmd->argv, environ);
}

int		 			foreground_execute(t_dispatch *const dispatch, t_cmd *const cmd)
{
	int 		status;
	pid_t 		parent;

	status = 0;
	if (cmd->is_builtin)
		return (cmd->is_builtin(dispatch, cmd->argv));
	else
	{
		parent = fork();
		if (!parent)
		{
			execute(cmd);
			if (cmd->argv && *cmd->argv)
				print("Binary not found : %s\n", 1, *cmd->argv);
			else
				print("Execve Fail :/\n", 0);
			exit(1);
		}
		else
			waitpid(parent, &status, 0);
		return (status);
	}
	return (ft_foreground_status(cmd));
}
