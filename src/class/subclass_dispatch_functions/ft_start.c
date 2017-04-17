/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 19:32:10 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/17 14:41:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void				ft_print_env(void)
{
	extern char			**environ;
	char				**ptr;

	ptr = environ;
	while (*ptr)
	{
		write(1, *ptr, LENS(*ptr));
		write(1, "\n", 1);
		ptr++;
	}
}

void					ft_start(t_dispatch *const dispatch)
{
	char				**split;

	split = ft_strsplit(dispatch->display->buffer, ft_isspace);
	if (split == NULL || *split == NULL)
		return ;
	//ft_print_env();
	write(1, "\n", 1);
	char *path = dispatch->environ->value("PATH");
	if (path)
		write(1, path, LENS(path));
	else
		write(1, "NULL", 4);
	dispatch->display->prompt(dispatch, PR_SUCCESS);
}
