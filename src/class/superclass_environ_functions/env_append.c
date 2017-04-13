/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 22:01:58 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/13 22:10:56 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			env_append(const char *full_value)
{
	extern char	**environ;
	char		**new;
	char		**ptr;

	if (!environ || !*environ)
		env_get_default();
	new = malloc(sizeof(char*) * env_count() + 1);
	ptr = new;
	if (!new)
		return ;
	while (*environ)
	{
		*ptr++ = ft_strsub(*environ);
		free(*environ++);
	}
	*ptr++ = ft_strsub(full_value);
	*ptr = NULL;
	environ = new;
}
