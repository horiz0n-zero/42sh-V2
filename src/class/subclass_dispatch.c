/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subclass_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:42:24 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/14 15:25:40 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static const t_class		g_description_environ =
{
	sizeof(t_environ), ft_environ_ctor, ft_environ_dtor
};

void						ft_dispatch_dtor(void *const self)
{
	pthread_mutex_destroy(&((t_dispatch*)self)->mutex);
	pthread_attr_destroy(&((t_dispatch*)self)->attribute);
	pthread_cond_destroy(&((t_dispatch*)self)->cond);
}

void				task_dispatch_fill(void *arg)
{
	t_dispatch		*dispatch;

	dispatch = (t_dispatch*)arg;
	dispatch->start = ft_start;
	pthread_attr_init(&dispatch->attribute);
	pthread_attr_setdetachstate(&dispatch->attribute, PTHREAD_CREATE_JOINABLE);
	pthread_mutex_init(&dispatch->mutex, NULL);
	pthread_mutex_unlock(&dispatch->mutex);
	pthread_cond_init(&dispatch->cond, NULL);
}

void						*ft_dispatch_ctor(const void *const self, ...)
{
	t_dispatch				*new;

	new = (t_dispatch*)malloc(sizeof(t_dispatch));
	if (new == NULL)
		return (NULL);
	new->based_class = self;
	task_dispatch_fill(new);
	if (pthread_create(&new->thread[0], &new->attribute, task_display_init, NULL))
		write(2, "#threadError\n", 13);
	if (pthread_create(&new->thread[1], &new->attribute, task_environ_init, NULL))
		write(2, "#threadError\n", 13);
	pthread_join(new->thread[0], (void*)&new->display);
	pthread_join(new->thread[1], (void*)&new->environ);
	return (new);
}
