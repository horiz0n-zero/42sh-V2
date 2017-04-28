/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subclass_foreground.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:57:16 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/28 13:33:24 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_class g_description_cmd =
{
	sizeof(t_cmd), ft_cmd_ctor, ft_cmd_dtor
};

static void 		ft_initialize_foreground(void)
{
	pid_t 			group;
	pid_t 			shell;

	if (isatty(STDIN_FILENO))
	{
		ft_catching_signal();
		/*
 		** ignorer par SIG_IGN les signaux attribués aux jobs controls
		*/
		while ((shell = getpgrp()) != (group = tcgetpgrp(STDIN_FILENO)))
			kill(shell, SIGTTIN);
		/*
		** tcgetpgrp retourne le process group id associer au terminal (0) si il est en foreground
		** getpgrp retourne le process groupe id du process actuel, 
		** en envoyant le signal SIGTTIN a son propre process group id, cela indique au processus parent de ceder
		** le foreground pour ce processus, la mise en boucle permet de s'assurer de pouvoir transmettre ce signal
		** non pas au parent mais aux parents.
		*/
		shell = getpid();
		setpgid(shell, group);
		/*
		** getpid() recuperer le processus id du process lui meme.
		** setpgid( pid_t process, pid_t group) set le group id du process id donner.
		*/
		tcsetpgrp(STDIN_FILENO, group);
		/*
 		** si le terminal (0) permet le job control, l'associer avec le group id du process.
		*/
	}
	else
		exit(1);
				/*
				** le job control ne fonctionne pas sur ce terminal.
				*/
}

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
	ft_initialize_foreground();
	return (new);
}

void 				ft_foreground_dtor(void *const self)
{
	free(self);
}
