/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks_hashable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:56:45 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/19 11:01:23 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_class	g_description_hashable =
{
	sizeof(t_hashable), ft_hashable_ctor, ft_hashable_dtor
};

void					*task_hashable_init(void *arg)
{
	arg = g_description_hashable.ctor(&g_description_hashable);
	return (arg);
}
