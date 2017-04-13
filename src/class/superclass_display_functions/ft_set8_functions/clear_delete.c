/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 15:33:37 by afeuerst          #+#    #+#             */
/*   Updated: 2017/03/28 18:15:26 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			ft_norme_delete(char *const ptr, t_dispatch *const dispatch)
{
	*ptr = 0;
	dispatch->display->apply(1, "dc");
}

void				ft_delete(t_dispatch *const dispatch)
{
	static int8_t	byte = 0;
	static char		*ptr = NULL;

	read(0, &byte, 1);
	if (*((ptr = dispatch->display->buffer + dispatch->display->index)))
	{
		if (*(ptr + 1))
		{
			ptr++;
			while (*ptr)
			{
				*(ptr - 1) = *ptr;
				ptr++;
			}
			*(ptr - 1) = 0;
			dispatch->display->apply(1, "ce");
			ptr = dispatch->display->index + dispatch->display->buffer;
			write(1, ptr, LENS(ptr));
			dispatch->display->mx(dispatch, LENI(ptr), GO_LEFT);
		}
		else
			ft_norme_delete(ptr, dispatch);
	}
	else
		dispatch->display->apply(2, "bl", "vb");
}

void				ft_clear(t_dispatch *const dispatch)
{
	static int32_t	byte = 0;

	read(0, &byte, sizeof(int32_t));
	if (*dispatch->display->buffer)
	{
		dispatch->display->mx(dispatch, dispatch->display->index, GO_LEFT);
		dispatch->display->index = 0;
		dispatch->display->apply(1, "ce");
		ft_memset_ll((int64_t*)dispatch->display->buffer,
							0, MAX_DISPLAY_CHAR / 8);
	}
	else
		dispatch->display->apply(2, "bl", "vb");
}
