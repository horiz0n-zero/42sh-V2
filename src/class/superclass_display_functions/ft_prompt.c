/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 15:54:34 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/19 12:20:33 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			ft_succes(t_dispatch *const dispatch, char *const buffer)
{
	write(1, "\e[32m< ", sizeof("\e[32m< "));
	write(1, buffer, LENS(buffer));
	write(1, " [ ", 3);
	write(1, dispatch->display->name.nodename,
			LENS(dispatch->display->name.nodename));
	write(1, " ]", 2);
	write(1, "\n> \e[37m", 8);
	dispatch->display->index = 0;
	dispatch->display->prompt_pos = 2;
	ft_memset_ll((int64_t*)dispatch->display->buffer, 0,
			MAX_DISPLAY_CHAR / 8);
}

static void			ft_failed(t_dispatch *const dispatch, char *const buffer)
{
	write(1, "\e[32m< ", sizeof("\e[32m< "));
	write(1, buffer, LENS(buffer));
	write(1, "\n\e[31m>> \e[37m", sizeof("\n\e[31m>> \e[37m"));
	dispatch->display->index = 0;
	dispatch->display->prompt_pos = 2;
	ft_memset_ll((int64_t*)dispatch->display->buffer, 0,
			MAX_DISPLAY_CHAR / 8);
}

static void			ft_quotes(t_dispatch *const dispatch, char *const buffer)
{
	write(1, "\e[32m< ", sizeof("\e[32m< "));
	write(1, buffer, LENS(buffer));
	write(1, "\n\e[34mquotes >\e[37m", sizeof("\n\e[34mquotes >\e[37m"));
	dispatch->display->prompt_pos = 8;
}

static const t_fpr	g_cor_prompt[] =
{
	[PR_SUCCESS] = ft_succes,
	[PR_FAILED] = ft_failed,
	[PR_QUOTES] = ft_quotes
};

void				ft_prompt(t_dispatch *const dispatch, const int32_t target)
{
	static char		buffer[8096];
	static t_fpr	ptr;

	ptr = g_cor_prompt[target];
	if (ptr)
	{
		getcwd(buffer, 8096);
		ptr(dispatch, buffer);
	}
}
