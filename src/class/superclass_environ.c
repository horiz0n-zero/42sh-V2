/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superclass_environ.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:56:38 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/13 22:18:33 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int					ft_change_key(const char *key, const char *value)
{
	extern char				**environ;
	char					**ptr;
	size_t					len;

	len = LENS(key);
	ptr = environ;
	if (!environ || !*environ)
		return (1);
	while (*ptr)
	{
		if (!ft_strncmp(key, *ptr, len))
		{
			free(*ptr);
			*ptr = ft_strincjoin(key, value, '=',
					malloc(len + LENS(value) + 2));
			return (0);
		}
		ptr++;
	}
	return (1);
}

static void					ft_load(void)
{
	extern char				**environ;
	char					**new;
	char					**ptr;

	new = malloc(sizeof(char*) * env_count());
	if (!new || !environ || !*environ)
	{
		env_get_default();
		return ;
	}
	ptr = new;
	while (*environ)
		*new++ = ft_strsub(*environ++);
	*new = NULL;
	environ = ptr;
}

void						*ft_environ_ctor(const void *const self, ...)
{
	t_environ				*environ;

	environ = (t_environ*)malloc(sizeof(t_environ));
	if (!environ)
		return (NULL);
	ft_load();
	environ->based_class = self;
	environ->get_required = env_guard;
	environ->modify = ft_change_key;
	environ->remove = env_remove;
	environ->append = env_append;
	environ->get_required();
	return (environ);
}

void						ft_environ_dtor(void *const self)
{
	free(self);
}
