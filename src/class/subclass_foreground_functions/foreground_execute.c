/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:57:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/26 18:37:49 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			foreground_launch(t_dispatch *const dispatch, t_cmd **array, size_t count)
{
	int				status;
	bool			ok;

	ok = true;
	while (count-- > 0)
	{
		status = dispatch->foreground->execute(dispatch, *array);
		if (status)
		{
			ok = false;
			print("\e[33m[%d] %s : %s\n\e[37m", 3, status, str_error(status), (*array)->argv);
		}
		((t_class*)dispatch->foreground->based_class_cmd)->dtor(*array++);
	}
	if (ok)
		dispatch->display->prompt(dispatch, PR_SUCCESS);
	else
		dispatch->display->prompt(dispatch, PR_FAILED);
}

static void			foreground_cmd(t_dispatch *const dispatch, char **argv, size_t count)
{
	t_cmd			*cmds[count];
	size_t			index;
	bool			ok;

	index = 0;
	ok = true;
	while (count-- > 0)
	{
		cmds[index] = ((t_class*)dispatch->foreground->based_class_cmd)->
			ctor(NULL, dispatch, argv);
		if (cmds[index]->is_ok == false || cmds[index]->is_illegal == true)
		{
			if (cmds[index]->argv && *cmds[index]->argv)
				print("\e[33mCommand not found : %s\n", 1, *cmds[index]->argv);
			dispatch->display->prompt(dispatch, PR_FAILED);
			return ;
		}
		index++;
		while (*argv)
			argv++;
		argv++;
	}
	foreground_launch(dispatch, cmds, index);
}

void				foreground_exec(t_dispatch *const dispatch, char *buffer)
{
	char			**split;
	char			**ptr;
	size_t			count;

	count = 1;
	split = ft_strsplit(buffer, ft_isspace);
	if (!split || !*split)
		return ;
	ptr = split;
	while (*ptr)
	{
		if (**ptr == ';' && !*(*ptr + 1) && *(ptr + 1))
		{
			count++;
			*ptr = NULL;
		}
		ptr++;
	}
	foreground_cmd(dispatch, split, count);
}
