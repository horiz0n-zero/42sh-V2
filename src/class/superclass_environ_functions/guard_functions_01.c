/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guard_functions_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 13:29:23 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/27 16:27:40 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char						*guard_home(const t_guard_struct guard)
{
	char					*login;
	char					*ptr;

	(void)guard;
	login = getlogin();
	if (!login)
		return (NULL);
	ptr = malloc(sizeof(char) * (LENS(login) + 13));
	if (!ptr)
		return (NULL);
	ft_strinjoin("HOME=/Users/", login, ptr);
	return (ptr);
}

char						*guard_lscolor(const t_guard_struct guard)
{
	(void)guard;
	return (ft_strsub("CLICOLOR=true"));
}
