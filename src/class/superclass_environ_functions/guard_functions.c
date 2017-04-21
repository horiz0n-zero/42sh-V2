/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guard_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:27:55 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 11:55:45 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char			*guard_term(const t_guard_struct guard)
{
	char		*new;
	char		*space;

	space = (char*)malloc(sizeof(char) * 20);
	if (!space)
		return (NULL);
	new = ft_strincjoin(guard.string, "xterm-256color", '=', space);
	return (new);
}

char			*guard_path(const t_guard_struct guard)
{
	char		*new;
	char		*space;

	space = (char*)malloc(sizeof(char) * 50);
	if (!space)
		return (NULL);
	new = ft_strincjoin(guard.string,
			"/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin", '=', space);
	return (new);
}

char			*guard_pwd(const t_guard_struct guard)
{
	char		*new;
	char		*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ft_strsub("PWD=???"));
	new = (char*)malloc(sizeof(char) * (LENS(path) + guard.len + 2));
	if (!new)
		return (ft_strsub("PWD=???"));
	new = ft_strincjoin(guard.string, path, '=', new);
	free(path);
	return (new);
}

char			*guard_shlvl(const t_guard_struct guard)
{
	(void)guard;
	return (ft_strsub("SHLVL=1"));
}

char			*guard_underscore(const t_guard_struct guard)
{
	char		*new;
	char		*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ft_strsub("_=???"));
	new = (char*)malloc(sizeof(char) * (LENS(path) + 3));
	if (!new)
		return (ft_strsub("_=???"));
	new = ft_strincjoin(guard.string, path, '=', new);
	free(path);
	return (new);
}
