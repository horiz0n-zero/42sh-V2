/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_file_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 13:15:09 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/18 14:52:46 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static size_t		ft_look(const char *split)
{
	DIR				*rep;
	size_t			count;

	count = 0;
	rep = opendir(split);
	while (readdir(rep))
		count++;
	closedir(rep);
	return (count);
}

size_t				ft_bin_count(t_dispatch *const dispatch)
{
	const char		*path;
	char			**split;
	size_t			count;
	char			**save;

	count = 0;
	path = dispatch->environ->value("PATH");
	split = ft_strsplit(ft_strsub(path), ft_isdoublepoint);
	save = split;
	if (split == NULL || *split == NULL)
		return (0);
	while (*split)
	{
		count += ft_look(*split++);
	}
	free(save);
	return (count);
}
