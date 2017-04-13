/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 18:03:23 by afeuerst          #+#    #+#             */
/*   Updated: 2017/03/28 18:10:51 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_strinjoin(const char *s1, const char *s2, char *in)
{
	if (in == NULL || s1 == NULL || s2 == NULL)
		return ;
	while (*s1)
		*in++ = *s1++;
	while ((*in++ = *s2++))
		continue ;
}

char		*ft_strincjoin(const char *s1, const char *s2, const char c,
		char *in)
{
	char		*ptr;

	ptr = in;
	if (in == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	while (*s1)
		*in++ = *s1++;
	*in++ = c;
	while ((*in++ = *s2++))
		continue ;
	return (ptr);
}

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (-1);
	while (n-- || *s1)
	{
		if (*s1 != *s2)
			return ((int)(*s1 - *s2));
		else if (!*s1)
			return (0);
		s1++;
		s2++;
	}
	return (0);
}

size_t		ft_strlen_sm(const char *str, const char c)
{
	size_t	count;

	count = 0;
	if (!str)
		return (count);
	while (*str && *str != c)
	{
		count++;
		str++;
	}
	return (count);
}

int			ft_strlen_im(const char *str, const char c)
{
	int		count;

	count = 0;
	if (!str)
		return (count);
	while (*str && *str != c)
	{
		str++;
		count++;
	}
	return (count);
}
