/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 19:32:10 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/13 13:55:06 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_fdis		g_cor_builtins[] =
{
	[1] = NULL
};



void					ft_start(t_dispatch *const dispatch)
{
	char				**split;

	split = ft_strsplit(dispatch->display->buffer, ft_isspace);
	if (split == NULL || *split == NULL)
		return ;
	dispatch->display->prompt(dispatch, PR_SUCCESS);
}
