/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:30:02 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 15:10:57 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			built_echo(t_dispatch *const dispatch, char **argv)
{
	bool	new_line;

	(void)dispatch;
	++argv;
	if (argv && *argv && **argv == '-' && *((*argv) + 1) == 'n')
	{
		new_line = false;
		argv++;
	}
	else
		new_line = true;
	while (argv && *argv)
	{
		write(1, *argv, LENS(*argv));
		if (*++argv)
			write(1, " ", 1);
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}
