/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superclass_hashable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:23:00 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/17 13:14:35 by afeuerst         ###   ########.fr       */
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
	return (hash->array[hash->key(key) % hash->size]);
}

void				*ft_hashable_ctor(const void *const self, ...)
{
	t_hashable		*new;

	new = malloc(sizeof(t_hashable));
	if (!new)
		return (NULL);
	new->key = ft_hashkey;
	new->get = ft_get;
	new->set = ft_set;
	new->size = 0; //todo//
	new->array = malloc(sizeof(char*) * new->size);
	ft_memset_ll((int64_t*)new->array, 0, new->size);
	return (new);
}

void				ft_hashable_dtor(void *const self)
{
	t_hashable		*hash;
	size_t			index;

	index = 0;
	hash = (t_hashable*)self;
	while (hash->size--)
	{
		if (hash->array[index])
		{
			;
		}
	}
}
