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

static void 	env_move(char **new)
{
	extern char **environ;
	char 		**ptr;

	ptr = environ;
	while (*ptr)
		*new++ = ft_strsub(*ptr++);
	*new = NULL;	
}

void			env_expand(t_environ *const env, const size_t count)
{
	extern char **environ;
	char 		**new;

	if (!environ)
		env->get_required(env);
	env->size += count;
	new = malloc(sizeof(char*) * (env->size + 1));
	if (!new)
		return ;
	env_move(new);
	env->kill();
	environ = new;
}
