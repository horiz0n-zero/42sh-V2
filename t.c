/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:38:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 16:48:33 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
# include <string.h>
#include <unistd.h>

typedef void	(*func)(va_list *args);

void				ft_push_string(va_list *args)
{
	char			*str;

	str = va_arg(*args, char*);
	write(1, str, strlen(str));
}

static const func	g_board_funcs[] =
{
	['s'] = ft_push_string
};

static void	ft_printf(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			g_board_funcs[(int)*++format](&args);
			format++;
		}
		else
			write(1, format++, 1);
	}
}

int		main(void)
{
	ft_printf("%s", "coucou");
}
