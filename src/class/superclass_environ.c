/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superclass_environ.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:56:38 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 12:19:27 by afeuerst         ###   ########.fr       */
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
	if (!new || !environ)
	{
		if (new)
			free(new);
		env_get_default(env);
		return ;
	}
	ptr = environ;
	while (*ptr)
		*new++ = ft_strsub(*ptr++);
	*new = NULL;
	environ = new - count;
	env->size = ENV_SPACE_AVAILABLE + count;
}

static const char			*ft_value(const char *key)
{
	extern char				**environ;
	char					**ptr;
	const char				*save;
	char					*env;

	save = key;
	ptr = environ;
	if (!ptr)
		return (NULL);
	while (*ptr)
	{
		env = *ptr++;
		while (*env && *key)
		{
			if (*env != *key)
				break ;
			env++;
			key++;
		}
		key = save;
		if (*env != '=')
			continue ;
		else
			return (++env);
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
	env->modify = env_modify;
	env->value = ft_value;
	env->count = ft_count;
	env->remove = env_remove;
	env->append = env_append;
	env->expand = env_expand;
	env->sort = env_sshell;
	ft_load(env);
	env->kill = env_kill;
	env->get_required(env);
	env->sort(env->count(0), environ, env->sort_type);
	return (env);
}

void						ft_environ_dtor(void *const self)
{
	((t_environ*)self)->kill();
	free(self);
}
