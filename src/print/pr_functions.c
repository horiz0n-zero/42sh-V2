/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 14:15:48 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/19 15:23:02 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void				ft_dfunc(const uint64_t raw, char *buffer)
{
	int				nb;
	int				number;

	number = *((int*)&raw);
	if (number < 0)
	{
		number = -number;
		*buffer++ = '-';
	}
	nb = number;
	if (number == 0)
		*buffer++ = '0';
	while (number)
	{
		buffer++;
		number /= 10;
	}
	*buffer = 0;
	while (nb)
	{
		*--buffer = nb % 10 + '0';
		nb /= 10;
	}
}

size_t				ft_dlen(va_list *args, uint64_t *raw, size_t *size)
{
	int				nb;
	size_t			len;

	len = 0;
	nb = (int)va_arg(*args, int);
	*raw = (uint64_t)nb & 0xFFFFFFFF;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	if (nb == 0)
		len++;
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	*size = *size + len;
	return (len);
}

void				ft_sfunc(const uint64_t raw, char *buffer)
{
	char			*str;

	str = (char*)raw;
	while (*str)
		*buffer++ = *str++;
	*buffer = 0;
}

size_t				ft_slen(va_list *args, uint64_t *raw, size_t *size)
{
	char			*str;
	size_t			len;

	len = 0;
	*raw = (uint64_t)(void*)va_arg(*args, void*);
	str = (char*)*raw;
	while (*str++)
		len++;
	*size = *size + len;
	return (len);
}
