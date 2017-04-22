/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:45:51 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 11:04:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/print.h"

static const t_printf	g_print_functions[] =
{
	['P'] = ft_ppfunc,
	['p'] = ft_pfunc,
	['s'] = ft_sfunc,
	['d'] = ft_dfunc,
	['u'] = NULL
};

static const t_printlen	g_pr_len[] =
{
	['P'] = ft_plen,
	['p'] = ft_plen,
	['s'] = ft_slen,
	['d'] = ft_dlen,
	['u'] = NULL
};

static void				join_print(char **board, const char *string,
		const size_t size)
{
	char				printable[size];
	int					index;
	char				*ptr;
	char				*str;

	ptr = printable;
	index = 0;
	while (*string)
	{
		if (*string == '%')
		{
			str = *board++;
			while (*str)
				*ptr++ = *str++;
			string += 2;
		}
		else
			*ptr++ = *string++;
	}
	*ptr = 0;
	write(1, printable, LENS(printable));
}

void					print(const char *string, int instructions, ...)
{
	char				*board[instructions];
	size_t				size;
	const char			*str;
	va_list				args;
	uint64_t			raw;

	va_start(args, instructions);
	str = string;
	instructions = 0;
	size = 1;
	while (*string)
	{
		size++;
		if (*string++ == '%')
		{
			board[instructions] = ALLOC(g_pr_len[(int)*string](&args, &raw, &size));
			g_print_functions[(int)*string++](raw, board[instructions++]);
		}
	}
	join_print(board, str, size);
}
