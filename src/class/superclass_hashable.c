/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superclass_hashable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:23:00 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/14 16:27:12 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void				*ft_hashable_ctor(const void *const self, ...)
{
	t_hashable		*new;

	new = malloc(sizeof(t_hashable));
	if (!new)
		return (NULL);
	return (new);
}

void				ft_hashable_dtor(void *const self)
{
	(void)self;
}
