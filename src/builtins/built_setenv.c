/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:27:38 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/24 19:32:52 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int				built_setenv(t_dispatch *const dispatch, char **argv)
{
	extern char **environ;

	argv++;
	if (argv && *argv)
	{
		while (*argv)
			dispatch->environ->append(dispatch->environ, *argv++);
		dispatch->environ->sort(dispatch->environ->count(0), environ,
								dispatch->environ->sort_type);
	}
	else
		print("\e[36msetenv \e[32m: remove all $VAR specified\n\e[37m", 0);
	return (0);
}
