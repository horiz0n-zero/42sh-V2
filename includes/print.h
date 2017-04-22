/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:42:40 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 13:28:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# ifdef print
#  undef print
# endif

# include <stdarg.h>
# include <unistd.h>

# ifdef ALLOC
#  undef ALLOC
# endif
# define ALLOC(size) __builtin_alloca(size)

# define BASE_TAB "0123456789ABCDEF"
# define BASE_TAB_S "0123456789abcdef"

typedef void	(*t_printf)(const uint64_t raw, char *buffer);
typedef size_t	(*t_printlen)(va_list *args, uint64_t *raw, size_t *size);
void			print(const char *string, const int instructions, ...);

size_t			ft_slen(va_list *args, uint64_t *raw, size_t *size);
size_t			ft_dlen(va_list *args, uint64_t *raw, size_t *size);
size_t			ft_plen(va_list *args, uint64_t *raw, size_t *size);

void			ft_ppfunc(const uint64_t raw, char *buffer);
void			ft_pfunc(const uint64_t raw, char *buffer);
void			ft_sfunc(const uint64_t raw, char *buffer);
void			ft_dfunc(const uint64_t raw, char *buffer);

#endif
