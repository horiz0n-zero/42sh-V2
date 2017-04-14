/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 22:01:58 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/14 16:07:44 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void			env_append(t_environ *const env, const char *full_value)
{
	extern char	**environ;

	if (!environ)
		env_get_default(env);
	if (env->size >= env->count(0))
		env->expand(env, GUARD_COUNT);
	environ[env->count(0)] = ft_strsub(full_value);
	environ[env->count(0) + 1] = NULL;
}
