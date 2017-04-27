/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks_hashable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:56:45 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/27 20:08:28 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_class	g_description_hashable =
{
	sizeof(t_hashable), ft_hashable_ctor, ft_hashable_dtor
};

void					*task_hashable_init(void *arg)
{
	t_hashable 			*hash;

	hash = g_description_hashable.ctor(&g_description_hashable, arg);
	hash->rm(hash, 8,
		"export", "setenv", "unsetenv", "echo", "env", "cd", "exit", "quit");
	hash->set(hash, "make", ft_strsub("/usr/bin/make"));
	return (hash);
}
