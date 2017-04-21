/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 21:51:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 11:55:21 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int				env_remove(t_environ *const env, const char *key)
{
	extern char	**environ;
	char		**ptr;

	(void)env;
	(void)key;
	ptr = environ;
	if (!ptr)
		return (1);
	while (*ptr)
	{
		;
	}
	return (0);
}
