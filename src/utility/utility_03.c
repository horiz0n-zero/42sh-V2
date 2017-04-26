/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 18:11:21 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/26 16:01:19 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool			compare(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (false);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (false);
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (false);
	return (true);
}

size_t			ft_strlen_magik(const char *str, const char c)
{
	size_t		len;

	len = 0;
	while (*str)
	{
		if (*str == c)
			return (len);
		str++;
	}
	return (~0);
}

char			*ft_strjoin(const char *s1, const char *s2)
{
	char		*new;
	char		*ptr;

	new = malloc(sizeof(char) * (LENS(s1) + LENS(s2) + 1));
	ptr = new;
	if (new == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	while (*s1)
		*ptr++ = *s1++;
	while ((*ptr++ = *s2++))
		continue ;
	return (new);
}

char			*ft_strcjoin(const char *s1, const char *s2, const char c)
{
	char		*new;
	char		*ptr;

	new = malloc(sizeof(char) * (LENS(s1) + LENS(s2) + 2));
	ptr = new;
	if (new == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	while (*s1)
		*ptr++ = *s1++;
	*ptr++ = c;
	while ((*ptr++ = *s2++))
		continue ;
	return (new);
}
