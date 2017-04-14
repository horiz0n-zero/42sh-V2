/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 13:51:19 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/14 16:11:49 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void			env_expand(t_environ *const env, const size_t count)
{
	extern char	**environ;
	char		**ptr;
	char		**new;

	new = malloc(sizeof(char*) * env->size + count + 1);
	if (!new || !environ)
		return ;
	ptr = new;
	while (*environ)
		*ptr++ = ft_strsub(*environ++);
	*ptr = NULL;
	env->size += count;
	environ = new;
}
