/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 22:15:19 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/13 22:20:30 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static const t_class	g_description_environ =
{
	sizeof(t_environ), ft_environ_ctor, ft_environ_dtor
};

void					*task_environ_init(void *arg)
{
	arg = g_description_environ.ctor(&g_description_environ);
	pthread_exit(arg);
}
