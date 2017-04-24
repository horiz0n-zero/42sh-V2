/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 21:42:46 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 15:51:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				ft_set8(const int8_t c, t_dispatch *const dispatch)
{
	static char		*buffer = NULL;

	if (c == 127)
		dispatch->display->unpush_byte(dispatch);
	else if (c == 27)
		((struct s_class*)dispatch)->dtor(dispatch);
	else if (c < 33)
	{
		if (c == ' ')
			dispatch->display->push_byte(dispatch, ' ');
		else if (c == '\t')
			; // ft_select
		else if (c == 13 && write(1, "\n", 1))
		{
			buffer = dispatch->display->buffer;
			while (ft_isspace(*buffer))
				buffer++;
			if (*buffer)
				dispatch->foreground->exec(dispatch, buffer);
			else
				dispatch->display->prompt(dispatch, PR_SUCCESS);
		}
	}
	else
		dispatch->display->push_byte(dispatch, c);
}
