/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:22:59 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 14:31:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int				built_env(t_dispatch *const dispatch)
{
	extern char	**environ;
	char		**ptr;

	(void)dispatch;
	ptr = environ;
	if (!ptr)
		return (1);
	while (*ptr)
		print("%s\n", 1, *ptr++);
	return (0);
}
