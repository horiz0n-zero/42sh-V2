/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superclass_hashable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:23:00 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 16:21:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static size_t		ft_hashkey(const char *key)
{
	size_t			hash_value;

	hash_value = 0;
	while (*key)
	{
		hash_value += *key++;
		hash_value += (hash_value << 10);
		hash_value ^= (hash_value >> 6);
	}
	hash_value += (hash_value << 3);
	hash_value ^= (hash_value >> 11);
	hash_value += (hash_value << 15);
	return (hash_value);
}

static void			ft_set(t_hashable *const hash, const char *key, char *data)
{
	hash->array[hash->key(key) % hash->size] = data;
}

static char			*ft_get(t_hashable *const hash, const char *key)
{
	char			*data;
	char			*cmp;
	const char		*save;

	save = key;
	data = hash->array[hash->key(key) % hash->size];
	if (data)
	{
		cmp = data;
		while (*cmp)
			cmp++;
		while (*key)
			key++;
		while (key > save && cmp > data && *key != '/')
		{
			if (*--key != *--cmp)
				return (NULL);
		}
		return (data);
	}
	return (NULL);
}

void				*ft_hashable_ctor(const void *const self, ...)
{
	t_hashable		*new;
	va_list			args;
	t_environ		*env;

	va_start(args, self);
	env = va_arg(args, void*);
	new = malloc(sizeof(t_hashable));
	if (!new)
		return (NULL);
	new->based_class = self;
	new->key = ft_hashkey;
	new->get = ft_get;
	new->set = ft_set;
	new->size = ft_bin_count(env);
	new->array = malloc(sizeof(char*) * new->size);
	ft_memset_ll((int64_t*)new->array, 0, new->size);
	hash_fill(new, env);
	new->rm = ft_hash_rm;
	new->refresh = hash_refresh;
	return (new);
}

void				ft_hashable_dtor(void *const self)
{
	t_hashable		*hash;
	char			**array;
	size_t			size;

	hash = self;
	if (!hash->array)
		return ;
	array = hash->array;
	size = hash->size;
	while (size-- > 0)
	{
		if (*array)
			free(*array);
		array++;
	}
	free(array);
}
