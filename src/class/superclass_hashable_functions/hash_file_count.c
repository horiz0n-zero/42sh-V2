/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_file_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 13:15:09 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/27 20:02:19 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static size_t		ft_look(const char *split)
{
	DIR				*rep;
	size_t			count;

	count = 1;
	rep = opendir(split);
	if (!rep)
		return (0);
	while (readdir(rep))
		count++;
	closedir(rep);
	return (count);
}

size_t				ft_bin_count(const t_environ *const env)
{
	size_t			count;
	char			**split;
	void			*ptr;
	char			*path;

	path = ft_strsub(env->value("PATH"));
	count = 1;
	split = ft_strsplit(path, ft_isdoublepoint);
	if (!split)
		return (count);
	ptr = split;
	while (*split)
		count += ft_look(*split++);
	free(ptr);
	free(path);
	return (count);
}
