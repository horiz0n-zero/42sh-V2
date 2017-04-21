/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:13:16 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 14:58:07 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_class	g_description_dispatch =
{
	sizeof(t_dispatch), ft_dispatch_ctor, ft_dispatch_dtor
};

static void				ft_while(t_dispatch *const dispatch)
{
	int8_t				capture;

	while ("minishell")
	{
		if (read(0, &capture, 1))
		{
			if (capture == '\e')
			{
				if (read(0, &capture, 1) && capture == '[')
				{
					read(0, &capture, 1);
					dispatch->display->set_24(capture, dispatch);
				}
				else
					((t_class*)dispatch)->dtor(dispatch);
			}
			else
				dispatch->display->set_8(capture, dispatch);
		}
	}
}

int						main(void)
{
	t_dispatch		*dispatch;

	dispatch = g_description_dispatch.ctor(&g_description_dispatch);
	if (dispatch == NULL || dispatch->display == NULL)
	{
		write(2, "Une erreur inconnue c'est produite\n", 36);
		return (1);
	}
	ft_catching_signal();
	dispatch->display->apply(1, "cl");
	ft_minishell();
	dispatch->display->prompt(dispatch, PR_SUCCESS);
	ft_while(dispatch);
	return (0);
}
