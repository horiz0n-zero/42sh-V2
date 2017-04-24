/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:57:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/24 19:36:45 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				foreground_exec(t_dispatch *const dispatch, char *buffer)
{
	t_cmd			*cmd;
	int				status;

	cmd = ((t_class*)dispatch->foreground->based_class_cmd)
		->ctor(NULL, dispatch, buffer);
	if ((status = dispatch->foreground->execute(dispatch, cmd)))
	{
		print("\e[33m%s %s\n", 2, str_error(status), buffer);
		dispatch->display->prompt(dispatch, PR_FAILED);
	}
	else
		dispatch->display->prompt(dispatch, PR_SUCCESS);
}
