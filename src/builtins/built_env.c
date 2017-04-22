/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:22:59 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 15:41:30 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void				built_env_print(void)
{
	extern char			**environ;
	char				**ptr;

	ptr = environ;
	if (!environ)
		return ;
	while (*ptr)
	{
		write(1, *ptr, LENS(*ptr));
		write(1, "\n", 1);
		ptr++;
	}
}

static const t_fbuil		g_functions[] =
{
	['i'] = env_i
};

int						built_env(t_dispatch *const dispatch, char **argv)
{

	(void)dispatch;
	argv++;
	if (argv && *argv)
	{
		if (**argv == '-')
		{
			if (g_functions[(int)*((*argv) + 1) & 0xFF])
				return (g_functions[(int)*((*argv) + 1)](dispatch, argv));
			else
				print("\e[36menv usage :\n-i remove env.\n\e[37m", 0);
		}
		else
			print("\e[36menv\e[32m usage :\n-i remove env.\n\e[37m", 0);
	}
	else
		built_env_print();
	dispatch->hashtable->refresh(dispatch);
	return (0);
}
