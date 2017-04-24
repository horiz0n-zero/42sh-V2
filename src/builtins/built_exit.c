/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:30:57 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/24 19:52:26 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			built_exit(t_dispatch *const dispatch, char **argv)
{
	(*(t_class**)dispatch)->dtor(dispatch);
	(void)argv;
	exit(0);
}
