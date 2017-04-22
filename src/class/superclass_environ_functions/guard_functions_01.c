/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guard_functions_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 13:29:23 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 16:22:07 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char						*guard_home(const t_guard_struct guard)
{
	struct passwd			*pass;
	char					*new;

	(void)guard;
	pass = getpwuid(getuid());
	new = malloc(sizeof(char) * (LENS(pass->pw_dir) + 1));
	if (!new)
		return (NULL);
	ft_memmove((int8_t*)new, (const int8_t*)pass->pw_dir, LENS(pass->pw_dir));
	return (new);
}
