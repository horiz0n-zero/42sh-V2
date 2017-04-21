/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 15:54:34 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 17:52:53 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			ft_succes(t_dispatch *const dispatch, char *const buffer)
{
	time_t			t;

	t = time(0);
	print("\e[32m< %s > %s \e[33m< %s\e[32m> \e[37m", 3, buffer,
			dispatch->display->name.nodename, ctime(&t));
	dispatch->display->index = 0;
	dispatch->display->prompt_pos = 2;
	ft_memset_ll((int64_t*)dispatch->display->buffer, 0,
			MAX_DISPLAY_CHAR / 8);
}

static void			ft_failed(t_dispatch *const dispatch, char *const buffer)
{
	print("\e[32m< %s\n\e[31m>> \e[37m", 1, buffer);
	dispatch->display->index = 0;
	dispatch->display->prompt_pos = 2;
	ft_memset_ll((int64_t*)dispatch->display->buffer, 0,
			MAX_DISPLAY_CHAR / 8);
}

static void			ft_quotes(t_dispatch *const dispatch, char *const buffer)
{
	print("\e[32m< %s\n\e[34mquotes >\e[37m", 1, buffer);
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
