/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superclass_environ.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:56:38 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/17 14:48:02 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static size_t				ft_count(size_t default_value)
{
	extern char				**environ;
	char					**ptr;

	ptr = environ;
	if (!ptr || !*ptr)
		return (0);
	while (*ptr++)
		default_value++;
	return (default_value);
}

static void					ft_load(t_environ *const env)
{
	extern char				**environ;
	char					**ptr;
	size_t					count;
	char					**new;

	count = env->count(0);
	new = malloc(sizeof(char*) * (count + 1 + ENV_SPACE_AVAILABLE));
	if (!count || !(ptr = new))
	{
		if (new)
			free(new);
		env_get_default(env);
		return ;
	}
	while ((*ptr++ = ft_strsub(*environ++)))
		continue ;
	environ = new;
	env->size = ENV_SPACE_AVAILABLE + count;
}

static char					*ft_value(const char *key)
{
	extern char				**environ;
	char					**ptr;
	const char				*ptr_value;
	char					*cmp;

	ptr = environ;
	while (*ptr)
	{
		ptr_value = key;
		cmp = *ptr++;
		while (*ptr_value)
		{
			if (*
		}
	}
	return (NULL);
}

void						*ft_environ_ctor(const void *const self, ...)
{
	t_environ				*env;
	extern char				**environ;

	env = (t_environ*)malloc(sizeof(t_environ));
	ft_memset((int8_t*)env, 0, sizeof(t_environ));
	if (!env)
		return (NULL);
	env->based_class = self;
	env->get_required = env_guard;
	env->value = ft_value;
	env->count = ft_count;
	env->remove = env_remove;
	env->append = env_append;
	env->expand = env_expand;
	env->sort = env_sshell;
	ft_load(env);
	env->get_required(env);
	env->sort(env->count(0), environ, env->sort_type);
	return (env);
}

void						ft_environ_dtor(void *const self)
{
	free(self);
}
