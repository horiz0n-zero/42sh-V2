/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_unpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:20:21 by afeuerst          #+#    #+#             */
/*   Updated: 2017/03/28 19:47:44 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int32_t		ft_push_check_norme(t_dispatch *const dispatch)
{
	if (dispatch->display->index >
		dispatch->display->screen.ws_col - dispatch->display->prompt_pos)
	{
		dispatch->display->apply(2, "bl", "vb");
		return (1);
	}
	return (0);
}

static void			ft_push_norme(t_dispatch *const dispatch, const int8_t c)
{
	write(1, &c, 1);
	*(dispatch->display->buffer + dispatch->display->index++) = c;
}

void				ft_push_byte(t_dispatch *const dispatch, const int8_t c)
{
	static char		*ptr = NULL;
	static char		*pos = NULL;

	if (ft_push_check_norme(dispatch))
		return ;
	if (*((ptr = dispatch->display->buffer + dispatch->display->index)))
	{
		dispatch->display->apply(1, "ce");
		write(1, &c, 1);
		write(1, ptr, LENS(ptr));
		dispatch->display->mx(dispatch, LENI(ptr), GO_LEFT);
		pos = ptr - 1;
		while (*ptr)
			ptr++;
		while (ptr > pos)
		{
			*(ptr + 1) = *ptr;
			ptr--;
		}
		*(pos + 1) = c;
		dispatch->display->index++;
	}
	else
		ft_push_norme(dispatch, c);
}

void				ft_unpush_byte(t_dispatch *const dispatch)
{
	static char		*ptr = NULL;

	if (dispatch->display->index <= 0)
	{
		dispatch->display->apply(2, "bl", "vb");
		return ;
	}
	if (*((ptr = dispatch->display->buffer + dispatch->display->index)))
	{
		while (*ptr)
		{
			*(ptr - 1) = *ptr;
			ptr++;
		}
		*(ptr - 1) = 0;
		dispatch->display->apply(2, "le", "dc");
		dispatch->display->index--;
	}
	else
	{
		*(dispatch->display->buffer + --dispatch->display->index) = 0;
		dispatch->display->apply(2, "le", "dc");
	}
}
