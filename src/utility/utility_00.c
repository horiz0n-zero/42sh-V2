/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:49:33 by afeuerst          #+#    #+#             */
/*   Updated: 2017/03/28 18:16:07 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			ft_memset(int8_t *ptr, const int8_t value, size_t len)
{
	if (ptr == NULL)
		return ;
	while (len-- > 0)
		*ptr++ = value;
}

void			ft_memset_ll(int64_t *ptr, const int64_t value, size_t len)
{
	if (ptr == NULL)
		return ;
	while (len-- > 0)
		*ptr++ = value;
}

int				ft_strlen_i(const char *str)
{
	int			len;

	len = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		str++;
		len++;
	}
	return (len);
}

size_t			ft_strlen_s(const char *str)
{
	size_t		len;

	len = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		str++;
		len++;
	}
	return (len);
}

void			ft_memmove(int8_t *dst, const int8_t *src, size_t len)
{
	if (dst == NULL || src == NULL || len == 0)
		return ;
	while (len-- > 0)
		*dst++ = *src++;
}
