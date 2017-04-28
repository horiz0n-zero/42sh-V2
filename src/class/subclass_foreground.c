/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subclass_foreground.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:57:16 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/28 16:57:08 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_class g_description_cmd =
{
	sizeof(t_cmd), ft_cmd_ctor, ft_cmd_dtor
};

/*static void 		ft_initialize_foreground(void)
{
	pid_t 			group;
	pid_t 			shell;

	if (isatty(STDIN_FILENO))
	{
		ft_catching_signal();
		while ((shell = getpgrp()) != (group = tcgetpgrp(STDIN_FILENO)))
			kill(shell, SIGTTIN);
		shell = getpid();
		setpgid(shell, group);
		tcsetpgrp(STDIN_FILENO, group);
	}
	else
		exit(1);
}
*/
void				*ft_foreground_ctor(const void *const self, ...)
{
	t_foreground 	*new;

	new = malloc(sizeof(t_foreground));
	if (!new)
		return (new);
	new->based_class = self;
	new->based_class_cmd = &g_description_cmd;
	new->exec = foreground_exec;
	new->execute = foreground_execute;
	ft_catching_signal();
	return (new);
}

void 				ft_foreground_dtor(void *const self)
{
	free(self);
}
