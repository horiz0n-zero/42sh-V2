/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:25:35 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 14:32:35 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			built_unsetenv(t_dispatch *const dispatch)
{
	(void)dispatch;
	print("unsetenv\n", 0);
	return (0);
}
