/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:29:07 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 15:10:53 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int			cd_last_position(char *last)
{
	if (chdir(last))
	{
		write(2, "cd - Failed\n", 12);
		return (1);
	}
	return (0);
}

static int			cd_go_home(t_dispatch *const dispatch)
{
	const char		*path;

	path = dispatch->environ->value("HOME");
	if (!path)
	{
		write(2, "cd required $HOME for this task\n", 32);
		return (1);
	}
	else
		return (chdir(path));
	return (0);
}

int					built_cd(t_dispatch *const dispatch, char **argv)
{
	static char		*last_position = NULL;
	static char		buffer[8096];

	(void)dispatch;
	getcwd(buffer, 8096);
	if (!last_position)
		free(last_position);
	last_position = ft_strsub(buffer);
	argv++;
	if (argv && *argv)
	{
		if (**argv == '~' && *((*argv) + 1) == '\0')
			return (cd_go_home(dispatch));
		if (**argv == '-' && *((*argv) + 1) == '\0')
			return (cd_last_position(last_position));
		if (**argv == '/')
			return (chdir(*argv));
		else
			return (chdir(ft_strincjoin(last_position, *argv, '/', buffer)));
	}
	else
		return (cd_go_home(dispatch));
	return (0);
}
