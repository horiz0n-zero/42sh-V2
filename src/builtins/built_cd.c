/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:29:07 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/25 12:27:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int 			cd_home(const char *home)
{
	if (!home)
	{
		print("cd : $HOME required.\n", 0);
		return (1);
	}
	if (chdir(home))
	{
		print("cd : $HOME have to be a real path.\n", 0);
		return (1);
	}
	return (0);
}

static int 			cd_move_path(const char *path)
{
	if (!path)
	{
		print("cd : $OLDPWD required.\n", 0);
		return (1);
	}
	if (chdir(path))
	{
		print("cd : %s No such file or directory\n", 1, path);
		return (1);
	}
	return (0);
}

int					built_cd(t_dispatch *const dispatch, char **argv)
{
	int 			status;
	char 			buffy[8096];

	argv++;
	if (argv && *argv)
	{
		if (**argv == '-' && !*(*argv + 1))
			status = cd_move_path(dispatch->environ->value("OLDPWD"));
		else if (**argv == '~' && !*(*argv + 1))
			status = cd_home(dispatch->environ->value("HOME"));
		else
			status = cd_move_path(*argv);
	}
	else
		status = cd_home(dispatch->environ->value("HOME"));
	if (dispatch->environ->modify("OLDPWD", dispatch->environ->value("PWD")))
		dispatch->environ->get_required(dispatch->environ);
	if (dispatch->environ->modify("PWD", getcwd(buffy, 8096)))
		dispatch->environ->get_required(dispatch->environ);
	return (status);
}
