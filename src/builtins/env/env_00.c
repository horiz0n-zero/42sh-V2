/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:13:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 15:24:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int				env_i(t_dispatch *const dispatch, char **argv)
{
	extern char	**environ;
	char		**ptr;

	ptr = environ;
	if (!environ)
		return (1);
	(void)dispatch;
	(void)argv;
	while (*ptr)
	{
		free(*ptr);
		*ptr++ = NULL;
	}
	free(environ);
	environ = NULL;
	return (0);
}
