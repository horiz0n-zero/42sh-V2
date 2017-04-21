/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:27:38 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/21 14:32:25 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			built_setenv(t_dispatch *const dispatch)
{
	dispatch->environ->append(dispatch->environ, "coco=setenv_ok");
	return (0);
}
