/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 22:01:58 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/27 15:24:17 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			env_append(t_environ *const env, const char *full_value)
{
	extern char **environ;
	size_t		size;

	if (!environ || !*environ)
		env->get_required(env);
	size = env->count(1);
	if (size >= env->size)
		env->expand(env, ENV_SPACE_AVAILABLE);
	environ[size] = NULL;
	environ[size - 1] = ft_strsub(full_value);
	env->sort(size, environ, env->sort_type);
}
