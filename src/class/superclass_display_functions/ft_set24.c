/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set24.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 22:44:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/03/28 18:14:58 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_fdis		g_set24_functions[] =
{
	['D'] = ft_move_left,
	['C'] = ft_move_right,
	['A'] = ft_arrow_up,
	['B'] = ft_arrow_down,
	['\e'] = ft_clear,
	['F'] = NULL,
	['H'] = NULL,
	['6'] = NULL,
	['5'] = NULL,
	['3'] = ft_delete
};

void					ft_set24(const int8_t value, t_dispatch *const dispatch)
{
	static t_fdis		function = NULL;
	static int32_t		bytes = 0;

	function = g_set24_functions[value];
	if (function)
		function(dispatch);
	else
		read(0, &bytes, 4);
}
