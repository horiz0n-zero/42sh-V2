/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 22:41:37 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/27 16:20:04 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static const t_class		g_description_display =
{
	sizeof(t_display), ft_display_ctor, ft_display_dtor
};

void						*task_display_init(void *arg)
{
	arg = g_description_display.ctor(&g_description_display);
	pthread_exit(arg);
}
