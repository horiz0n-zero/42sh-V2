/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_function_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:50:28 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 11:06:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/print.h"

size_t				ft_plen(va_list *args, uint64_t *raw, size_t *size)
{
	uint64_t		value;
	size_t			count;

	count = 4;
	value = (uint64_t)va_arg(*args, void*);
	*raw = value;
	if (!value)
		count++;
	while (value > 0)
	{
		count++;
		value /= 16;
	}
	*size = *size + count;
	return (count);
}

void				ft_ppfunc(const uint64_t raw, char *buffer)
{
	uint64_t		save;

	save = raw;
	*buffer++ = '0';
	*buffer++ = 'x';
	*buffer++ = '0';
	if (!save)
		*buffer++ = '0';
	while (save > 0)
	{
		buffer++;
		save /= 16;
	}
	*buffer = 0;
	save = raw;
	while (save > 0)
	{
		*--buffer = BASE_TAB_S[save % 16];
		save /= 16;
	}
}

void				ft_pfunc(const uint64_t raw, char *buffer)
{
	uint64_t		save;

	save = raw;
	*buffer++ = '0';
	*buffer++ = 'x';
	*buffer++ = '0';
	if (!save)
		*buffer++ = '0';
	while (save > 0)
	{
		buffer++;
		save /= 16;
	}
	*buffer = 0;
	save = raw;
	while (save > 0)
	{
		*--buffer = BASE_TAB[save % 16];
		save /= 16;
	}
}
