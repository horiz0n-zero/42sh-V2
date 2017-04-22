/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:25:35 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 15:08:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			built_unsetenv(t_dispatch *const dispatch, char **argv)
{
	argv++;
	if (*argv)
		while (*argv)
			dispatch->environ->remove(dispatch->environ, *argv++);
	else
		print("\e[36munsetenv \e[32m: remove every $VAR specified\n", 0);
	return (0);
}
