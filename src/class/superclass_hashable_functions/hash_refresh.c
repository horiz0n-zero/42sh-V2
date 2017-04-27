/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_refresh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:32:58 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/27 20:14:39 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void		hash_refresh(t_dispatch *const dispatch)
{
	char	**array;
	size_t	size;

	size = dispatch->hashtable->size;
	array = dispatch->hashtable->array;
	while (size-- > 0)
	{
		if (*array)
			free(*array);
		array++;
	}
	free(dispatch->hashtable->array);
	dispatch->hashtable->size = ft_bin_count(dispatch->environ);
	dispatch->hashtable->array = malloc(sizeof(char*) *
			dispatch->hashtable->size);
	if (!dispatch->hashtable->array)
		return ;
	ft_memset_ll((int64_t*)dispatch->hashtable->array, 0,
			dispatch->hashtable->size);
	hash_fill(dispatch->hashtable, dispatch->environ);
	dispatch->hashtable->rm(dispatch->hashtable, 8,
		"echo", "setenv", "unsetenv", "env", "quit", "exit", "cd", "export");
	dispatch->hashtable->set(dispatch->hashtable, "make",
			ft_strsub("/usr/bin/make"));
}
