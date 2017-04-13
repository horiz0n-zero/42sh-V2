/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:54:25 by afeuerst          #+#    #+#             */
/*   Updated: 2017/03/28 18:12:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				ft_mx(t_dispatch *const dispatch, int x, const int n)
{
	static char		*property = NULL;
	static size_t	len = 0;

	(void)dispatch;
	if (n & GO_LEFT)
	{
		property = tgetstr("le", NULL);
		if (property)
			len = LENS(property);
	}
	else
	{
		property = tgetstr("nd", NULL);
		if (property)
			len = LENS(property);
	}
	if (!property)
		return ;
	while (x-- > 0)
		write(1, property, len);
}

void				ft_my(t_dispatch *const dispatch, int y, const int n)
{
	static char		*property = NULL;
	static size_t	len = 0;

	(void)dispatch;
	if (n & GO_UP)
	{
		property = tgetstr("up", NULL);
		if (property)
			len = LENS(property);
	}
	else
	{
		property = tgetstr("do", NULL);
		if (property)
			len = LENS(property);
	}
	while (y-- > 0)
		write(1, property, len);
}
