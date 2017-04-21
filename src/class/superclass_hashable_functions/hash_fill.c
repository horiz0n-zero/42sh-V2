/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 13:42:58 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 17:43:49 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static void				hash_search(t_hashable *const hash, const char *path)
{
	DIR					*rep;
	struct dirent		*tmp;
	struct stat			c;
	char				*data;

	rep = opendir(path);
	while ((tmp = readdir(rep)))
	{
		data = ft_strcjoin(path, tmp->d_name, '/');
		stat(data, &c);
		if (S_ISREG(c.st_mode) && c.st_mode & S_IXUSR && !(*tmp->d_name == '.'))
			hash->set(hash, tmp->d_name, data);
		else
			free(data);
	}
	closedir(rep);
}

void					hash_fill(t_hashable *const hash, t_environ *const env)
{
	char				*path;
	char				**split;
	void				*wfree;

	path = ft_strsub(env->value("PATH"));
	split = ft_strsplit(path, ft_isdoublepoint);
	if (!split)
		return ;
	wfree = split;
	while (*split)
		hash_search(hash, *split++);
	free(path);
	free(wfree);
}
