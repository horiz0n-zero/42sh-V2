/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catching_signal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 21:12:42 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 11:57:09 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void						sfunc_sigint(void)
{
	;
}

static void						sfunc_sigquit(void)
{
	;
}

static const t_signal_function	g_functions[] =
{
	[SIGINT] = sfunc_sigint,
	[SIGQUIT] = sfunc_sigquit
};

void							ft_do_nothing(int signal)
{
	static t_signal_function	function = NULL;

	if ((function = g_functions[signal]))
		function();
}

void							ft_catching_signal(void)
{
	if (signal(SIGINT, ft_do_nothing) == SIG_ERR)
		write(2, "SIGINT catch error\n", sizeof("SIGINT catch error\n"));
	if (signal(SIGQUIT, ft_do_nothing) == SIG_ERR)
		write(2, "SIGQUIT catch error\n", sizeof("SIGINT catch error\n"));
}
