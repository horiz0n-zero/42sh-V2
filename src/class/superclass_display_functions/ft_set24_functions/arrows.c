/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:13:07 by afeuerst          #+#    #+#             */
/*   Updated: 2017/03/28 19:43:50 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			ft_move_left(t_dispatch *const dispatch)
{
	if (dispatch->display->index <= 0)
	{
		dispatch->display->apply(2, "bl", "vb");
		return ;
	}
	dispatch->display->index--;
	dispatch->display->apply(1, "le");
}

void			ft_move_right(t_dispatch *const dispatch)
{
	if (dispatch->display->index >= LENI(dispatch->display->buffer))
	{
		dispatch->display->apply(2, "bl", "vb");
		return ;
	}
	dispatch->display->index++;
	dispatch->display->apply(1, "nd");
}

void			ft_arrow_up(t_dispatch *const dispatch)
{
	(void)dispatch;
}

void			ft_arrow_down(t_dispatch *const dispatch)
{
	(void)dispatch;
}
