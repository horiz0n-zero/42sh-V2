/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subclass_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:42:24 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/28 13:33:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_class		g_description_foreground =
{
	sizeof(t_foreground), ft_foreground_ctor, ft_foreground_dtor
};

void						ft_dispatch_dtor(void *const self)
{
	t_dispatch				*dispatch;

	dispatch = self;
	pthread_mutex_destroy(&dispatch->mutex);
	pthread_attr_destroy(&dispatch->attribute);
	pthread_cond_destroy(&dispatch->cond);
	(*(t_class**)dispatch->environ)->dtor(dispatch->environ);
	(*(t_class**)dispatch->display)->dtor(dispatch->display);
	(*(t_class**)dispatch->hashtable)->dtor(dispatch->hashtable);
	(*(t_class**)dispatch->foreground)->dtor(dispatch->foreground);
	exit(0);
}

void						task_dispatch_fill(void *arg)
{
	t_dispatch		*dispatch;

	dispatch = (t_dispatch*)arg;
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
	pthread_create(&new->thread[0], &new->attribute, task_environ_init, NULL);
	pthread_create(&new->thread[1], &new->attribute, task_display_init, NULL);
	new->foreground = g_description_foreground.ctor(&g_description_foreground);
	pthread_join(new->thread[0], (void**)&new->environ);
	pthread_create(&new->thread[2], &new->attribute, task_hashable_init,
			new->environ);
	pthread_join(new->thread[1], (void**)&new->display);
	pthread_join(new->thread[2], (void**)&new->hashtable);
	return (new);
}
