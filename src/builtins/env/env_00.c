/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:13:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/27 17:01:21 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				env_n(t_dispatch *const dispatch)
{
	dispatch->environ->kill();
	env_get_default(dispatch->environ);
	chdir(dispatch->environ->value("PWD"));
	dispatch->hashtable->refresh(dispatch);
	return (0);
}

int				env_r(t_dispatch *const dispatch)
{
	extern char	**environ;

	dispatch->environ->sort_type = F_REV_ASCII;
	if (!environ)
		dispatch->environ->get_required(dispatch->environ);
	dispatch->environ->sort(dispatch->environ->count(0),
			environ, dispatch->environ->sort_type);
	dispatch->hashtable->refresh(dispatch);
	return (0);
}

int				env_a(t_dispatch *const dispatch)
{
	extern char	**environ;

	dispatch->environ->sort_type = F_ASCII;
	if (!environ)
		return (0);
	dispatch->environ->sort(dispatch->environ->count(0),
			environ, dispatch->environ->sort_type);
	dispatch->hashtable->refresh(dispatch);
	return (0);
}

int				env_i(t_dispatch *const dispatch)
{
	dispatch->environ->kill();
	dispatch->hashtable->refresh(dispatch);
	return (0);
}
