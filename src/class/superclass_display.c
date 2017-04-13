/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superclass_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:20:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/03/28 17:37:24 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				ft_putchar(int signal)
{
	return ((int)write(1, &signal, 1));
}

static void		ft_apply_capacity(int32_t count, ...)
{
	char		*action;
	va_list		args;

	va_start(args, count);
	while (count-- > 0)
	{
		action = tgetstr(va_arg(args, char*), NULL);
		tputs(action, 0, ft_putchar);
	}
	va_end(args);
}

static void		ft_push_functions(t_display *const display)
{
	display->apply = ft_apply_capacity;
	display->set_8 = ft_set8;
	display->set_24 = ft_set24;
	display->push_byte = ft_push_byte;
	display->unpush_byte = ft_unpush_byte;
	display->prompt = ft_prompt;
	display->mx = ft_mx;
	display->my = ft_my;
	ft_memset_ll((int64_t*)display->buffer, 0, MAX_DISPLAY_CHAR / 8);
	display->index = 0;
}

void			*ft_display_ctor(const void *const self, ...)
{
	t_display	*new;

	new = (t_display*)malloc(sizeof(t_display));
	if (new == NULL)
		return (NULL);
	if (tgetent(NULL, "xterm-256color") == -1)
		abort();
	if (tcgetattr(0, &new->term) == -1)
		return (NULL);
	new->origin = new->term;
	new->term.c_iflag &= ~(INLCR | IGNCR | ICRNL | IGNPAR | INPCK);
	new->term.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(0, TCSADRAIN, &new->term) == -1)
		return (new);
	new->based_class = self;
	new->screen.ws_col = tgetnum("co");
	new->screen.ws_row = tgetnum("li");
	ft_push_functions(new);
	return (new);
}

void			ft_display_dtor(void *const self)
{
	t_display	*display;

	display = self;
	tcsetattr(0, TCSADRAIN, &display->origin);
	free(self);
}
