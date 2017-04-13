/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:54:34 by afeuerst          #+#    #+#             */
/*   Updated: 2017/03/28 18:03:18 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				ft_isdoublepoint(const int c)
{
	return (c == ':');
}

int				ft_isspace(const int c)
{
	return (c == ' ' || c == '\n');
}

char			*ft_strsub(const char *src)
{
	char		*new;
	char		*ptr;

	new = malloc(sizeof(char) * (LENS(src) + 1));
	ptr = new;
	if (new == NULL)
		return (NULL);
	while (*src)
		*ptr++ = *src++;
	*ptr = 0;
	return (new);
}

static size_t	ft_count(const char *str, int (*f)(int))
{
	size_t		count;

	count = 1;
	if (str == NULL)
		return (1);
	while (*str)
	{
		if (f(*str))
		{
			while (*str && f(*str))
				str++;
		}
		else
		{
			while (*str && !f(*str))
				str++;
			count++;
		}
	}
	return (count);
}

char			**ft_strsplit(char *str, int (*f)(int))
{
	char		**ptr;
	char		**c;

	c = (char**)malloc(sizeof(char*) * (ft_count(str, f)));
	ptr = c;
	if (!ptr)
		return (NULL);
	while (*str)
	{
		if (f(*str))
		{
			while (*str && f(*str))
				*str++ = 0;
		}
		else
		{
			*ptr++ = str;
			while (*str && !f(*str))
				str++;
		}
	}
	*ptr = NULL;
	return (c);
}
