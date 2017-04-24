/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:13:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 16:26:01 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int				env_n(t_dispatch *const dispatch, char **argv)
{
	(void)argv;
	dispatch->environ->kill();
	env_get_default(dispatch->environ);
	return (0);
}

int				env_r(t_dispatch *const dispatch, char **argv)
{
	extern char	**environ;

	(void)argv;
	dispatch->environ->sort_type = F_REV_ASCII;
	if (!environ)
		return (0);
	dispatch->environ->sort(dispatch->environ->count(0),
			environ, dispatch->environ->sort_type);
	return (0);
}

int				env_a(t_dispatch *const dispatch, char **argv)
{
	extern char	**environ;

	(void)argv;
	dispatch->environ->sort_type = F_ASCII;
	if (!environ)
		return (0);
	dispatch->environ->sort(dispatch->environ->count(0),
			environ, dispatch->environ->sort_type);
	return (0);
}

int				env_i(t_dispatch *const dispatch, char **argv)
{
	extern char **environ;
	char 		**ptr;

	(void)argv;
	ptr = environ;
	while (*ptr)
	{
		free(*ptr);
		*ptr++ = NULL;
	}
	dispatch->environ->get_required(dispatch->environ);
	return (0);
}
