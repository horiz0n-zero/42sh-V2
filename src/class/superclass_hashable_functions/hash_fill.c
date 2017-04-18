/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 13:42:58 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/18 14:53:15 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"



static void			ft_fill_split(t_hashable *const hash, const char *path)
{
	DIR				*reper;
	struct dirent	*tmp;
	char			*join;
	char			buffer[8096];
	struct stat		chat;

	reper = opendir(path);
	while ((tmp = readdir(reper)))
	{
		join = ft_strincjoin(path, tmp->d_name, '/', buffer);
		stat(join, &chat);
		if (!S_ISREG(chat.st_mode) ||
			!(S_IXGRP & chat.st_mode) ||
			!(S_IXUSR & chat.st_mode))
			continue ;
		hash->set(hash, tmp->d_name, ft_strsub(join));
	}
	closedir(reper);
}

void				hash_fill(t_dispatch *const dispatch)
{
	char			**split;
	const char		*path;

	path = dispatch->environ->value("PATH");
	split = ft_strsplit(ft_strsub(path), ft_isdoublepoint);
	if (!split || !*split)
		return ;
	while (*split)
		ft_fill_split(dispatch->hashtable, *split++);
}
