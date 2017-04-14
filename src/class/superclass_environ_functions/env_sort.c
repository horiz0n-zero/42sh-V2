/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 14:42:36 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/14 16:17:26 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static int			sort_ascii(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
		{
			if (*s1 > *s2)
				return (1);
			else
				return (0);
		}
		s1++;
		s2++;
	}
	return (0);
}

static int			sort_rev_ascii(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
		{
			if (*s1 < *s2)
				return (1);
			else
				return (0);
		}
		s1++;
		s2++;
	}
	return (0);
}

static const f_sort	g_condition_functions[3] =
{
	[F_ASCII] = sort_ascii,
	[F_REV_ASCII] = sort_rev_ascii,
	[F_UNKNOW] = NULL
};

void				env_sshell(const int count, char **array, const int func)
{
	int				i;
	int				j;
	int				space;
	const f_sort	function = g_condition_functions[func];
	char			*tmp;

	space = count / 2;
	i = 0;
	j = space;
	while (j > 0)
	{
		while (j < count)
		{
			if (function(IVALUE, JVALUE))
			{
				tmp = JVALUE;
				JVALUE = IVALUE;
				IVALUE = tmp;
			}
			j++;
			i++;
		}
		i = 0;
		j = --space;
	}
}
