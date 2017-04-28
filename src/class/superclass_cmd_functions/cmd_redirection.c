/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:51:30 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/26 16:43:36 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void  		ignore_arg(char **argv)
{
	while (*argv)
	{
		*argv = *(argv + 1);
		argv++;
	}
	*(argv - 1) = NULL;
}

static int  		redirection_path(char *path, const int type, const int def)
{
	int 			fd;

	if (!path)
		return (def);
	if (!type)
	{
		fd = open(path, O_RDWR | O_TRUNC);
		if (fd == -1)
			fd = open(path, O_TRUNC | O_CREAT | O_RDWR);
		return (fd);
	}
	else
	{
		fd = open(path, O_WRONLY | O_APPEND);
		if (fd == -1)
			fd = open(path, O_TRUNC | O_CREAT | O_RDWR);
		return (fd);
	}
	return (def);
}

static void 		redirection_right(t_cmd *const cmd, char *r,  char *path)
/*     **
** '>' **
**     */
{
	int 			fd;

	fd = 1;
	if (*r >= '0' && *r <= '2')
		fd = *r++ - '0';
	if (*r == '>' && !*(r + 1))
	{
		if (fd == 0)
			cmd->stdin = redirection_path(path, 0, STDIN_FILENO);
		else if (fd == 1)
			cmd->stdout = redirection_path(path, 0, STDOUT_FILENO);
		else if (fd == 2)
			cmd->stderr = redirection_path(path, 0, STDERR_FILENO);
	}
	else if (*r == '>' && *(r + 1) == '>' && !*(r + 2))
	{
		if (fd == 0)
			cmd->stdin = redirection_path(path, 1, STDIN_FILENO);
		else if (fd == 1)
			cmd->stdout = redirection_path(path, 1, STDOUT_FILENO);
		else if (fd == 2)
			cmd->stdout = redirection_path(path, 1, STDERR_FILENO);
	}
	else
	{
		cmd->is_ok = false;
		print("Parse error near >\n", 0);
	}
}

static void 		redirection_left(t_cmd *const cmd, char *r, char *path)
/*     **
** '<' **
**     */
{
	int 			fd;

	if (*(r + 1) == '<' && !*(r + 2) && path)
	{
		fd = open(path, O_RDONLY);
		if (cmd->stdin != STDIN_FILENO)
			close(cmd->stdin);
		if (fd != -1)
			cmd->stdin = fd;
	}
	else if (!*(r + 1) && path)
	{
		fd = open(path, O_RDONLY);
		if (cmd->stdin != STDIN_FILENO)
			close(cmd->stdin);
		if (fd != 1)
			cmd->stdin = fd;
	}
	else
	{
		cmd->is_ok = false;
		print("Parse error near <\n", 0);
	}
}

void 				cmd_redirection(t_cmd *const cmd, char **argv)
{
	char 			*ptr;

	while (*argv)
	{
		ptr = *argv;
		while (*ptr)
		{
			if (*ptr == '>')
			{
				redirection_right(cmd, *argv, *(argv + 1));
				ignore_arg(argv);
				if (*argv)
					ignore_arg(argv--);
				break ;
			}
			else if (*ptr == '<')
			{
				redirection_left(cmd, *argv, *(argv + 1));
				ignore_arg(argv);
				if (*argv)
					ignore_arg(argv--);
				break ;
			}
			else
				ptr++;
		}
		argv++;
	}
}
